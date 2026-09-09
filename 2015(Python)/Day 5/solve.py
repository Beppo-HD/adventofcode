import re


FILENAME = "input.txt"

def check_nice_string(s):
    return 1 if sum(1 if cur in "aeiou" else 0 for cur in s) >= 3 and bool(re.search(r'(.)\1', s)) and not any(sub in s for sub in ["ab", "cd", "pq", "xy"]) else 0


def check_nicer_string(s):
    return 1 if bool(re.search(r'(..).*\1', s)) and bool(re.search(r'(.).\1', s)) else 0


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Nice strings:", sum(check_nice_string(line) for line in lines))
    print("Nicer strings:", sum(check_nicer_string(line) for line in lines))