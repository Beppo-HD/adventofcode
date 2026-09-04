
FILENAME = "1.txt"
CHAR_UP = "("
CHAR_DOWN = ")"


def count_chars(s, chars):
    char_counts = {}
    for c in chars:
        char_counts[c] = s.count(c)
    return char_counts

def find_first_negative_diff(s):
    pos = 0
    step = 1
    for c in s:
        if c == CHAR_UP:
            pos += 1
        else:
            pos -= 1
            if pos < 0:
                break
        step += 1
    return step

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    counts = count_chars(lines[0], [CHAR_UP, CHAR_DOWN])
    print(counts)
    print("End position:", counts["("] - counts[")"])
    print("First negative:", find_first_negative_diff(lines[0]))