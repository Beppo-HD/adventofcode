import itertools

FILENAME = "13.txt"

def parse_preferences(lines):
    preferences = {}
    for line in lines:
        first, _, sign, units, _, _, _, _, _, _, second = line.split(" ")
        if first not in preferences:
            preferences[first] = {}
        preferences[first][second[:-1]] = int(units) if sign == "gain" else -int(units)
    return preferences

def check_permutations(preferences):
    people = preferences.keys()
    best_total = 0
    for combination in itertools.permutations(people, len(people)):
        current_total = 0
        for i in range(len(people)):
            current_person = combination[i]
            current_total += preferences[current_person][combination[(i-1) % len(people)]] + preferences[current_person][combination[(i+1) % len(people)]]
        if current_total > best_total:
            best_total = current_total
    return best_total
            

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    preferences = parse_preferences(lines)
    print("Best score for friends:", check_permutations(preferences))
    preferences["me"] = {}
    for person in list(preferences.keys()):
        preferences[person]["me"] = 0
        preferences["me"][person] = 0
    print("Best score for friends including myself:", check_permutations(preferences))
    