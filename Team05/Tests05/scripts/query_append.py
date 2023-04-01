import os
lines_per_group = 5  # number of lines to process at once

query_file_path = "../milestone_3/Multi_clause_7_queries.txt"
# read the starting number from the separate file
if os.path.exists(query_file_path) and os.path.getsize(query_file_path) > 0:
    # Read the starting number from the 5th last line of the file
    with open(query_file_path, "r") as f:
        starting_number = int(f.readlines()[-5].split()[0]) + 1
else:
    # Starting file does not exist or is empty, set starting number to 1
    starting_number = 1

# process the input file
with open("queries.txt", "r") as f:
    lines = f.readlines()

for i in range(0, len(lines), 5):
    line = lines[i].split()
    line[0] = str(starting_number)
    lines[i] = " ".join(line) + "\n"
    starting_number += 1

# Print the modified other file to console
with open(query_file_path, "a") as f:
    f.write("\n")
    f.write("".join(lines))