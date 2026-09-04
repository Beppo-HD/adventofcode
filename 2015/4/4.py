import hashlib
import itertools

FILENAME = "4.txt"
    
def find_nx0_hash(key, n):
    for i in itertools.count(start = 0):
        s = key + str(i)
        if hashlib.md5(s.encode()).hexdigest()[:n] == '0' * n:
            return i


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Five zeros:", find_nx0_hash(lines[0], 5))
    print("Six zeros:", find_nx0_hash(lines[0], 6))