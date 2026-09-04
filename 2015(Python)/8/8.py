import re

FILENAME = "8.txt"

def decode_string(s):
    s = s[1:-1]
    return re.sub(r'\\x([0-9a-fA-F]{2})|\\"|\\\\', lambda m: chr(int(m.group(1), 16)) if m.group(1) else m.group()[1], s)


def encode_string(s):
    s = re.sub(r'["\\]', lambda m: '\\' + m.group(), s)
    return '\"' + s + '\"'

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Diff to decoded:", sum(len(line) for line in lines) - sum(len(decode_string(line)) for line in lines))
    print("Diff to encoded:", sum(len(encode_string(line)) for line in lines) - sum(len(line) for line in lines))