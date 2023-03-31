import os
import glob
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

def process_out_xml(out_xml):
    root = ET.parse(out_xml).getroot()
    queries = root.findall(".//query")
    corrected_queries = []

    for query in queries:
        if query.find("timeout") is not None:
            continue
        if query[5].tag == "passed":
            continue
        # Only include failed queries (i.e queries that do have answers)
        comment = query[0].attrib["comment"]
        query_str = query.find("querystr").text
        decl_end = query_str.find("Select")
        formatted_query_str = query_str[:decl_end] + "\n" + query_str[decl_end:]
        correct_ans = query[5].find("additional").text
        corrected_queries.append((comment, formatted_query_str, correct_ans))
    return corrected_queries
       

def write_correct_queries_file(corrected_queries, query_file_path):
    ctr = 1
    with open(query_file_path, "w") as f:
        for comment, query, answer in corrected_queries:
            f.write(f"{ctr} - {comment}\n")
            ctr += 1
            f.write(f"{query}\n")
            f.write(f"{answer}\n")
            f.write(f"5000\n")
        
    f.close()

if __name__ == "__main__":
    if len(sys.argv) < 3:
     raise Exception(f"Intended usage: python3 out_generator.py path_to_correct_out_xml path_to_new_queries_file")
  
    corrected_queries = process_out_xml(sys.argv[1])
    write_correct_queries_file(corrected_queries, sys.argv[2])
