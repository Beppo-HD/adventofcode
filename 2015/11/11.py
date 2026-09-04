import string
import re

FILENAME = "11.txt"

def iterate_string(s):
    if s[len(s) - 1] == 'z':
        return iterate_string(s[:-1]) + "a"
    return s[:len(s) - 1] + chr(ord(s[len(s) - 1]) + 1)

def check_string(s):
    return (any(string.ascii_lowercase[i:i+3] in s for i in range(len(string.ascii_lowercase) - 2)) and all(x not in s for x in "iol") and bool(re.search(r'(.)\1.*(.)\2', s)))

def find_next_password(s):
    while not check_string(s):
        s = iterate_string(s)
    return s

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    first_password = find_next_password(lines[0])
    print("New password:", first_password)
    print("Another password:", find_next_password(iterate_string(first_password)))