import os
import glob
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
    Returns a dictionary in the form { "test_name": [max, average, max_query_string], ... }.

    :param out_xmls: the list of out.xml files to process 
    """

    result_dict = {}
    global_maximum = 0
    global_maximum_query = ""
    global_average = 0
    global_query_count = 0

    for out_xml in out_xmls:
        test_name = os.path.basename(out_xml)[:-len(out_xml_suffix)]
        root = ET.parse(out_xml).getroot()
        queries = root.findall(".//query")
        
        local_maximum = 0
        local_maximum_query = ""
        local_average = 0

        for query in queries:
            time = float(query[4].text)
            if time > local_maximum:
                local_maximum = time
                local_maximum_query = query[1].text
            local_average += float(time)

            if time > global_maximum:
                global_maximum = time
                global_maximum_query = f"{test_name} - {query[1].text}"

            global_average += time
            global_query_count += 1

        result_dict[test_name] = [local_maximum, 
                                  round(local_average/len(queries), 3),
                                  local_maximum_query.replace("\n", "")]
    
    result_dict["Global"] = [global_maximum, 
                             round(global_average/global_query_count, 3), 
                             global_maximum_query.replace("\n", "")]
    return result_dict

def write_results(result_dict, out_path, raw_out_path):
    """
    Writes out the resulting dictionary to the out file.

    :param result_dict: the dictionary to write out, { "test_name": [max, average, max_query_string], ... }.
    :param outh_path: the path of the file to write out to
    """

    previous_run = {}
    if os.path.exists(raw_out_path):
        with open(raw_out_path, "r") as raw_out:
            previous_run = eval(raw_out.read())

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
    if not previous_result:
        previous_result = [0, 0, ""]
    new_max, new_avg, new_max_query = result
    prev_max, prev_avg, prev_max_query = previous_result

    max_diff = f"({'↑' if new_max - prev_max > 0 else '↓'} {new_max - prev_max})"
    avg_diff = f"({'↑' if new_avg - prev_avg > 0 else '↓'} {new_avg - prev_avg})"

    return f"### {test_name}\n" + \
           f"#### Maximum\n" + \
           f"- Current run: {new_max} {max_diff}\n" + \
           f"- Current query: {new_max_query}\n" + \
           f"- Previous run: {prev_max}\n" + \
           f"- Previous query: {prev_max_query}\n\n" + \
           f"#### Average\n" + \
           f"- Current run: {new_avg} {avg_diff}\n" + \
           f"- Previous run: {prev_avg}\n" + \
           f"{divider}"

if __name__ == "__main__":
    out_xmls = get_out_xmls()
    result_dict = process_out_xmls(out_xmls)
    write_results(result_dict,
                  os.path.join(test_dir, out_analysis_filename),
                  os.path.join(test_dir, raw_out_analysis_filename))
