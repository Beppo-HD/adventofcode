import json
import re

FILENAME = "12.txt"

def sum_all_digits(s):
    return sum(int(num) for num in re.findall(r'-?\d+', s))

def sum_ignoring_red(data):
    if isinstance(data, int):
        return data
    elif isinstance(data, list):
        return sum(sum_ignoring_red(item) for item in data)
    elif isinstance(data, dict):
        if "red" in data.values():
            return 0
        return sum(sum_ignoring_red(value) for value in data.values())
    return 0

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Sum of all digits:", sum_all_digits(lines[0]))
    print("Sum ignoring red:", sum_ignoring_red(json.loads(lines[0])))