import itertools
import random

# read the input file
with open('tempfiles/input.txt', 'r') as f:
    text = f.read()

# split the text into words
words = text.split()

# generate all possible permutations of 7 words
combinations = itertools.permutations(words, 7)

# read the start and end strings from files
with open('tempfiles/start_string.txt', 'r') as f:
    start_string = f.read().strip()

with open('tempfiles/end_string.txt', 'r') as f:
    end_string = f.read().strip()

# shuffle the permutations in random order
combinations = list(combinations)
random.shuffle(combinations)

# limit the number of permutations to 50 or the total number of possible permutations, whichever is smaller
num_permutations = min(len(combinations), 50)
combinations = combinations[:num_permutations]

# write the combinations to the output file with the combination number and start/end strings
with open('tempfiles/output.txt', 'w') as f:
    for i, c in enumerate(combinations):
        # add the start and end strings to the combination
        c = start_string + ' '  + ' and '.join(c) + '\n' + end_string
        # write the combination with the combination number
        f.write(str(i + 1) + ' - ' + c + '\n')