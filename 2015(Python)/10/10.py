import re

FILENAME = "10.txt"

def Look_and_say(s, steps):
    if steps > 0:
        return Look_and_say(re.sub(r'(.)\1*', lambda m: str(len(m.group(0))) + m.group(1), s), steps - 1)
    return s
    

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    step_40 = Look_and_say(lines[0], 40)
    print("Digits after 40 steps:", len(step_40))
    print("Digits after 50 steps:", len(Look_and_say(step_40, 10)))