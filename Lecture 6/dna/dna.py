import csv
import sys


def main():

    # TODO: Check for command-line usage
    check_command_line_arguments(sys.argv)




    # TODO: Read database file into a variable

    my_dict = csv_to_dict(sys.argv[1])

    # TODO: Read DNA sequence file into a variable

    txt_file = open(sys.argv[2], "r").read()

    # print(txt_file)



    # TODO: Find longest match of each STR in DNA sequence

    for row_dict in my_dict:

        if find_match(row_dict, longest_match, txt_file):
            print(row_dict["name"])
            sys.exit(0)

    print("No match")
    sys.exit(1)




    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

def check_command_line_arguments(sys_object):

    if len(sys_object) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)


def csv_to_dict(csv_path):
    _csv = open(csv_path, "r")

    my_dict = csv.DictReader(_csv)

    return my_dict


def find_match(dictt, func, txt):

    counter = 0

    for key, value in dictt.items():
        if key != "name":
            # print(f"My value {value} vs my value sequence {func(txt, key)}")
            if int(value) == int(func(txt, key)):
                counter += 1


    if counter == len(dictt) - 1:
        return True
    return False



main()
