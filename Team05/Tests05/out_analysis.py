import os
import glob
import argparse
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

test_dir = Path(__file__).resolve().parent
out_xml_suffix = "_out.xml"
out_analysis_filename = "out_analysis.md"
raw_out_analysis_filename = "out_analysis_raw.txt"
divider = "----\n\n"

def get_out_xmls():
    """
    Returns list of all out.xml file names
    """

    return glob.glob(os.path.join(os.getcwd(), "**/*" + out_xml_suffix), recursive=True)

def process_out_xmls(out_xmls):
    """
    Calculates the global/local maximum and average query time for the given out.xml files.
    Returns a dictionary in the form { 
        "test_name": [max, total_time, max_query_string, total_queries], .
    .. }.

    :param out_xmls: the list of out.xml files to process 
    """

    result_dict = {}
    global_maximum = 0
    global_maximum_query = ""
    global_total_time = 0
    global_query_count = 0
    global_num_timeout = 0

    for out_xml in out_xmls:
        print(f"Processing {out_xml}")
        test_name = os.path.basename(out_xml)[:-len(out_xml_suffix)]
        root = ET.parse(out_xml).getroot()
        queries = root.findall(".//query")
        
        local_maximum = 0
        local_maximum_query = ""
        local_total_time = 0
        local_num_timeout = 0

        for query in queries:
            if query.find("timeout") is not None:
                time = 5000
                local_num_timeout += 1
            else:
                time = float(query[4].text)
            if time > local_maximum:
                local_maximum = time
                local_maximum_query = query[1].text
            local_total_time += float(time)

            if time > global_maximum:
                global_maximum = time
                global_maximum_query = f"{test_name} - {query[1].text}"

            global_total_time += time
            global_query_count += 1

        result_dict[test_name] = [local_maximum, 
                                  local_total_time,
                                  local_maximum_query.replace("\n", ""),
                                  local_num_timeout,
                                  len(queries)]
        global_num_timeout += local_num_timeout
    
    result_dict["Global"] = [global_maximum, 
                             global_total_time, 
                             global_maximum_query.replace("\n", ""),
                             global_num_timeout,
                             global_query_count]
    return result_dict

def write_results(result_dict, out_path, raw_out_path, branch):
    """
    Writes out the resulting dictionary to the out file.

    :param result_dict: the dictionary to write out, { "test_name": [max, average, max_query_string], ... }.
    :param outh_path: the path of the file to write out to
    """

    previous_run = {}
    if branch: # compare output from master branch
        subprocess.run(['git', 'checkout', branch])
    if os.path.exists(raw_out_path):
        with open(raw_out_path, "r") as raw_out:
            previous_run = eval(raw_out.read())
    if branch:
        subprocess.run(['git', 'checkout', '-'])

    # Overwrite the raw file
    with open(raw_out_path, "w") as raw_out:
        raw_out.write(str(result_dict))

    f = open(out_path, "w")

    # sort key alphabetically ignoring case except for "Global" which will be first element
    sorted_dict = {key: result_dict[key] for key in sorted(result_dict.keys(), key=lambda x: x.lower()) if key != "Global"}
    sorted_dict = {"Global": result_dict["Global"], **sorted_dict}
    for test_name, result in sorted_dict.items():
        formatted_statistic = format_statistic(test_name, result, previous_run.get(test_name))
        f.write(formatted_statistic)
        
    f.close()

def format_statistic(test_name, result, previous_result):
    """
    Returns a formatted markdown string for a given test statistic.

    :param test_name: the name of the test
    :param result: the current result of the test
    :param previous_result: the previous result of the test
    """

    new_max, total_time, new_max_query, new_num_timeout, total_queries = result
    new_avg = round(total_time / total_queries, 3) if total_queries else 0
    
    if not previous_result:
        previous_result = [0, 0, "", 0]
    prev_max, previous_total_time, prev_max_query, prev_num_timeout, prev_total_queries = previous_result
    prev_avg = round(previous_total_time / prev_total_queries, 3) if prev_total_queries else 0

    max_diff = round(new_max - prev_max, 3)
    max_diff_str = get_diff_str(max_diff, 1)
    avg_diff = round(new_avg - prev_avg, 3)
    avg_diff_str = get_diff_str(avg_diff, 0.5)
    num_timeout_diff = new_num_timeout - prev_num_timeout;
    num_timeout_diff_str = get_diff_str(num_timeout_diff, 0)

    return f"### {test_name}\n" + \
           f"#### Overall statistics\n" + \
           f"- Total time {round(total_time, 3)} (previously {round(previous_total_time, 3)})\n" + \
           f"- {total_queries} queries, (previously {prev_total_queries})\n\n" + \
           f"#### Maximum\n" + \
           f"- Current run: {new_max} {max_diff_str}\n" + \
           f"- Current query: {new_max_query}\n" + \
           f"- Previous run: {prev_max}\n" + \
           f"- Previous query: {prev_max_query}\n\n" + \
           f"#### Average\n" + \
           f"- Current run: {new_avg} {avg_diff_str}\n" + \
           f"- Previous run: {prev_avg}\n" + \
           f"#### Timeout\n" + \
           f"- Number of queries that timed out: {new_num_timeout} {num_timeout_diff_str}\n\n" + \
           f"{divider}"

def get_diff_str(diff, threshold):
    return highlight_str(f"({'↑' if diff > 0 else '↓'} {diff})", diff, threshold)

def highlight_str(str, diff, threshold):
    if diff > threshold:
        return f"<mark style='background-color: lightpink'>{str}</mark>"
    elif diff < -threshold:
        return f"<mark style='background-color: lightgreen'>{str}</mark>"
    else:
        return str

if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser(description='Script to extract query evaluation statistics')
    arg_parser.add_argument('-l', dest='local', action='store_true', help='Set to run locally')
    arg_parser.add_argument('-b', dest='branch', help='The branch to compare to')
    arg_parser.add_argument('-t', dest='tests', nargs="*", help='The test names to analyse')
    args = arg_parser.parse_args()
    
    if args.local:
        out_path = "docs/out_analysis_local.md"
        raw_out_path = "docs/out_analysis_raw_local.txt"
    else:
        out_path = os.path.join("docs", out_analysis_filename)
        raw_out_path = os.path.join("docs", raw_out_analysis_filename)
    
    if args.tests:
        cwd = os.getcwd()
        out_xmls = [os.path.join(cwd, "Team05/Tests05/out", f"{test_name}_out.xml") for test_name in args.tests]
    else:
        out_xmls = get_out_xmls()

    result_dict = process_out_xmls(out_xmls)
    write_results(result_dict,
                  out_path,
                  raw_out_path,
                  args.branch)
