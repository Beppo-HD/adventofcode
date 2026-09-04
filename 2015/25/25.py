import math

FILENAME = "25.txt"
FIRST_CODE = 20151125
MULTIPLY_BY = 252533
MODULO_BY = 33554393

def parse_pos(s):
    _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, row, _, col = s.split() 
    return (int(row[:-1]), int(col[:-1]))

def find_val_at_pos(pos):
    current_pos = (1, 1)
    current_code = FIRST_CODE
    while current_pos != pos:
        if current_pos[0] == 1:
            current_pos = (current_pos[1] + 1, 1)
        else:
            current_pos = (current_pos[0] - 1, current_pos[1] + 1)
        current_code = (current_code * MULTIPLY_BY) % MODULO_BY
    return current_code

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print(find_val_at_pos(parse_pos(lines[0])))
    