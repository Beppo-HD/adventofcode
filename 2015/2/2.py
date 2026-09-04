import math

FILENAME = "2.txt"

def wrapping_paper(s):
    dimensions = [int(x) for x in s.split('x')]
    d1, d2, d3 = dimensions
    return 2*(d1*d2 + d2*d3 + d1*d3) + (math.prod(sorted(dimensions)[:-1]))
    

def ribbon(s):
    dimensions = [int(x) for x in s.split('x')]
    return 2*sum(x for x in sorted(dimensions)[:-1]) + math.prod(dimensions)


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Total paper needed:", sum(wrapping_paper(line) for line in lines))
    print("Total ribbon needed:", sum(ribbon(line) for line in lines))