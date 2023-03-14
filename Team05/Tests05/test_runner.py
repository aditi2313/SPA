import os
import platform
import subprocess
import glob
import xml.etree.ElementTree as ET
import sys
from pathlib import Path
from typing import Literal

test_dir = Path(__file__).resolve().parent
source_file_suffix = "_source.txt"
queries_file_suffix = "_queries.txt"
output_file_suffix = "_out.xml"
output_dir = os.path.join(test_dir, "out")

autotester_path_mac = \
        "../Code05/cmake-build-debug/src/autotester/autotester"
autotester_path_windows = \
        "../Code05/out/build/x64-Debug/src/autotester/autotester.exe"
autotester_path =  os.path.join(test_dir, autotester_path_windows) \
            if platform.system() == "Windows" \
            else os.path.join(test_dir, autotester_path_mac)

def run_testcase(testname):
    print(f'Running testcase {testname}')
    source_file = testname + source_file_suffix
    queries_file = testname + queries_file_suffix
    output_file = os.path.join(output_dir, testname + output_file_suffix)
    result = subprocess.run([autotester_path, source_file, queries_file, output_file], 
                   capture_output=True)
    if result.stderr:
        return f"Failed: {testname} Error: {result.stderr}"
    else:
        print(f'Ran {testname}')
        total_failed_queries = count_failed_queries(output_file)
        if (total_failed_queries > 0): 
            return f"Failed: {testname} Total failures: {total_failed_queries}"
    

def find_all_testcases():
    testcases = []
    # all *_source.txt files in current directory and its subdirectories
    txt_files = glob.glob(os.path.join(os.getcwd(), "**/*" + source_file_suffix), recursive=True)
    for f in txt_files:
        testname = f[:-len(source_file_suffix)]
        query_file = testname + queries_file_suffix
        if not os.path.exists(query_file):
            raise f'Missing queries file for {testname}'
        testcases.append(testname)
    return testcases

def count_failed_queries(out_file):
    tree = ET.parse(out_file)
    root = tree.getroot()

    count = 0
    for query in root.findall('./queries/query'):
        if query.find('failed'):
            count += 1
    
    return count

def print_colour(str, colour: Literal["red", "green", "yellow", "blue"]):
    colour_code = 31 if colour == "red" \
            else 32 if colour == "green" \
            else 33 if colour == "yellow" \
            else 34
    print(f"\033[{colour_code}m {str} \033[0m")

if __name__ == "__main__":
    if (len(sys.argv) > 1):
        autotester_path = sys.argv[1] # passed in from github actions
    testcases = find_all_testcases()
    errors = []
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    for tc in testcases:
        error = run_testcase(tc)
        if error:
            errors.append(error)
    
    for error in errors:
        print_colour(error, "red")
    
    if errors:
        sys.exit(1)
    else:
        print_colour("All system tests run successfully!", "green")
        sys.exit(0)

