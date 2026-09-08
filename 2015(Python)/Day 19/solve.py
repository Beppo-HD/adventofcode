FILENAME = "input.txt"

def parse_input(lines):
    transitions = {}
    for line in lines:
        pieces = line.split(" ")
        if len(pieces) == 3:
            replaced, _, replacement = pieces
            if replaced not in transitions:
                transitions[replaced] = []
            transitions[replaced].append(replacement)
        else:
            medicine = pieces[0]
    return (transitions, medicine)

def count_possible_transitions(s, transitions):
    total_transitions = set()
    for replaceable in transitions.keys():
        for replacement in transitions[replaceable]:
            occurrences = s.count(replaceable)
            for pos in range(1, occurrences + 1):
                total_transitions.add(replace_nth(s, replaceable, replacement, pos))
    return len(total_transitions)

def count_steps(transitions, medicine):
    steps = 0
    while medicine != "e":
        for replaceable in transitions.keys():
            for replacement in transitions[replaceable]:
                after_replace = medicine.replace(replacement, replaceable, 1)
                if medicine != after_replace:
                    medicine = after_replace
                    steps += 1
    return steps

        
def replace_nth(s, replace, replacement, occurrences):
    parts = s.split(replace)
    return replace.join(parts[:occurrences]) + replacement + replace.join(parts[occurrences:]) if len(parts) > occurrences else s

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    input = parse_input(lines)
    print("Possible transitions from start-string:", count_possible_transitions(input[1], input[0]))
    print("Levenshtein distance:", count_steps(input[0], input[1]))