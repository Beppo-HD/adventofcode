import re

FILENAME = "input.txt"

def lights_command(s, grid, phase):
    if s.startswith("turn on "):
        s = s[len("turn on "):]
        action = lambda x : (x + 1) if phase == 2 else 1
    elif s.startswith("turn off "):
        s = s[len("turn off "):]
        action = lambda x : (x - 1 if x > 0 else 0) if phase == 2 else 0
    elif s.startswith("toggle "):
        s = s[len("toggle "):]
        action = lambda x : (x + 2) if phase == 2 else (1 if x != 1 else 0)
    else:
        return

    x1, y1, x2, y2 = (int(num) for num in re.findall(r'\d+', s))
    for i in range(x1, x2 + 1):
        for j in range(y1, y2 + 1):
            grid[i][j] = action(grid[i][j])
    return grid


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    for phase, label in ((1, "Lights:"), (2, "Lights new rules:")):
        grid = [[0] * 1000 for _ in range(1000)]
        for line in lines:
            grid = lights_command(line, grid, phase)
        print(label, sum(sum(row) for row in grid))