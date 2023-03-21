import os
import glob
import xml.etree.ElementTree as ET
from pathlib import Path

test_dir = Path(__file__).resolve().parent
out_xml_suffix = "_out.xml"
out_analysis_filename = "out_analysis.txt"

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
                global_maximum_query = f"{test_name}: {query[1].text}"

            global_average += time
            global_query_count += 1

        result_dict[test_name] = [local_maximum, 
                                  round(local_average/len(queries), 3),
                                  local_maximum_query.replace("\n", "")]
    
    result_dict["Global"] = [global_maximum, 
                             round(global_average/global_query_count, 3), 
                             global_maximum_query.replace("\n", "")]
    return result_dict

def write_results(result_dict, out_path):
    """
    Writes out the resulting dictionary to the out file.

    :param result_dict: the dictionary to write out
    :param outh_path: the path of the file to write out to
    """

    f = open(out_path, "w")

    f.write(f"Global maximum: {result_dict['Global'][0]}s = {result_dict['Global'][2]}\n" + \
            f"Global average: {result_dict['Global'][1]}s\n")
    
    sorted_dict_ignore_case = dict(sorted(result_dict.items(), key=lambda i: i[0].lower()))
    for test_name, result in sorted_dict_ignore_case.items():
        if(test_name == "Global"): continue
        f.write(f"{test_name} maximum: {result[0]}s = {result[2]}\n" + \
                f"{test_name} average: {result[1]}s\n")

    f.close()

if __name__ == "__main__":
    out_xmls = get_out_xmls()
    result_dict = process_out_xmls(out_xmls)
    write_results(result_dict, os.path.join(test_dir, out_analysis_filename))
