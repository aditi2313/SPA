import os
import sys

#script to append queries onto existing file without having to manually rename them.
#arg1 is the existing file you want to append to, arg2 is the file that contains the new queries you have genearted.


lines_per_group = 5  # number of lines to process at once
if len(sys.argv) < 3:
     raise Exception(f"Intended usage: python3 query_append.py path_to_existing_queries.txt path_to_new_queries_file")
original_file_path = sys.argv[1]
new_query_file_path = sys.argv[2]
# read the starting number from the separate file
if os.path.exists(original_file_path) and os.path.getsize(original_file_path) > 0:
    # Read the starting number from the 5th last line of the file
    with open(original_file_path, "r") as f:
        starting_number = int(f.readlines()[-5].split()[0]) + 1
else:
    # Starting file does not exist or is empty, set starting number to 1
    starting_number = 1

# process the input file
with open(new_query_file_path, "r") as f:
    lines = f.readlines()

for i in range(0, len(lines), 5):
    line = lines[i].split()
    line[0] = str(starting_number)
    lines[i] = " ".join(line) + "\n"
    starting_number += 1

# Print the modified other file to console
with open(original_file_path, "a") as f:
    f.write("\n")
    f.write("".join(lines))