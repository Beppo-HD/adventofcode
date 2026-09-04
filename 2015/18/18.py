import copy

FILENAME = "18.txt"
STEPS = 100

def parse_field(lines):
    field = []
    for line in lines:
        row = []
        for c in line:
            row.append(True if c == '#' else False)
        field.append(row)
    return field

def Conway_step(field, corners=False):
    new_field = []
    for i in range(len(field)):
        new_row = []
        for j in range(len(field[i])):
            neighbours = 0
            pos_to_check = [(i-1, j-1), (i-1, j), (i-1, j+1), (i, j-1), (i, j+1), (i+1, j-1), (i+1, j), (i+1, j+1)]
            for pos in pos_to_check:
                if 0 <= pos[0] < len(field) and 0 <= pos[1] < len(field[i]):
                    neighbours += 1 if field[pos[0]][pos[1]] else 0
            new_row.append(True if neighbours in [2, 3] and field[i][j] else True if neighbours == 3 and not field[i][j] else False)
        new_field.append(new_row)
    if corners:
        rows, cols = len(field), len(field[0])
        new_field[0][0] = True
        new_field[0][cols - 1] = True
        new_field[rows - 1][0] = True
        new_field[rows - 1][cols - 1] = True
    return new_field

def count_alive(field):
    count = 0
    for row in field:
        for col in row:
            count += 1 if col else 0
    return count

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    original_field = parse_field(lines)
    field = copy.deepcopy(original_field)
    for i in range(STEPS):
        field = Conway_step(field)
    print("Cells alive after", STEPS, "steps:", count_alive(field))
    field = copy.deepcopy(original_field)
    rows, cols = len(field), len(field[0])
    field[0][0] = True
    field[0][cols - 1] = True
    field[rows - 1][0] = True
    field[rows - 1][cols - 1] = True
    for i in range(STEPS):
        field = Conway_step(field, True)
    print("Cells alive after", STEPS, "steps with corners always alive:", count_alive(field))