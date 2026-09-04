import itertools

FILENAME = "9.txt"

def parse_distances(lines):
    distances = {}
    for line in lines:
        first, _, second, _, distance = line.split(" ")
        if first not in distances:
            distances[first] = {}
        if second not in distances:
            distances[second] = {}
        distances[first][second] = distance
        distances[second][first] = distance
    return distances

def find_path(distances, criteria):
    best_distance = None
    best_route = []
    for route in list(itertools.permutations(distances.keys())):
        cur_distance = 0
        for idx, loc in enumerate(route):
            if idx > 0:
                cur_distance += int(distances[loc][prev_loc])
            prev_loc = loc
        if best_distance is None or criteria(cur_distance, best_distance):
            best_distance = cur_distance
            best_route = route
    return best_distance, best_route

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    distances = parse_distances(lines)
    shortest_route = find_path(distances, lambda x, y: x < y)
    print(" -> ".join(loc for loc in shortest_route[1]), "=", shortest_route[0])
    longest_route = find_path(distances, lambda x, y: x > y)
    print(" -> ".join(loc for loc in longest_route[1]), "=", longest_route[0])