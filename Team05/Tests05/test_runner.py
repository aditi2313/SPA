import os
import platform
import subprocess
import glob
from pathlib import Path

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
        print(result.stderr)
    else:
        print(f'{testname} successfully ran')
    

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

if __name__ == "__main__":
    testcases = find_all_testcases()
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    for tc in testcases:
        run_testcase(tc)
