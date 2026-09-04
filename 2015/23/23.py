import math

FILENAME = "23.txt"
state = {
    "registers":{
        "a":0,
        "b":0
    },
    "program_counter":0
}

def parse_program(lines):
    program = []
    for line in lines:
        parts = line.split(" ")
        if len(parts) == 3:
            parts[1] = parts[1][:-1]
        program.append(parts)
    return program

def run_program(program):
    while state["program_counter"] < len(program):
        parts = program[state["program_counter"]]

        match parts[0]:
            case "hlf":
                state["registers"][parts[1]] //= 2
                state["program_counter"] += 1
            case "tpl":
                state["registers"][parts[1]] *= 3
                state["program_counter"] += 1
            case "inc":
                state["registers"][parts[1]] += 1
                state["program_counter"] += 1
            case "jmp":
                state["program_counter"] += int(parts[1])
            case "jie":
                if state["registers"][parts[1]] % 2 == 0:
                    state["program_counter"] += int(parts[2])
                else:
                    state["program_counter"] += 1
            case "jio":
                if state["registers"][parts[1]] == 1:
                    state["program_counter"] += int(parts[2])
                else:
                    state["program_counter"] += 1


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    program = parse_program(lines)
    run_program(program)
    print("Value in register b after program is run:", state["registers"]["b"])
    state["program_counter"] = 0
    state["registers"] = {"a": 1, "b": 0}
    run_program(program)
    print("Value in register b when a starts at 1:", state["registers"]["b"])