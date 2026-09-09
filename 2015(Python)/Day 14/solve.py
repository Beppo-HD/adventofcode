FILENAME = "input.txt"
FLYING_SECONDS = 2503

def parse_stats(lines):
    stats = []
    for line in lines:
        name, _, _, speed, _, _, active, _, _, _, _, _, _, resting, _ = line.split(" ")
        stats.append((name, speed, active, resting))
    return stats

def calculate_distances(stats, seconds):
    distances = []
    for stat in stats:
        current_distance = 0
        cycle = int(stat[2]) + int(stat[3])
        for i in range(seconds):
            if i % cycle < int(stat[2]):
                current_distance += int(stat[1])
        distances.append((current_distance, stat[0]))
    return distances

def calculate_points(stats, seconds):
    points = {}
    for i in range(1, seconds + 1):
        distances = calculate_distances(stats, i)
        cur_best = max(distances)
        for distance in distances:
            if distance[0] == cur_best[0]:
                if distance[1] not in points:
                    points[distance[1]] = 0
                points[distance[1]] += 1
    return points

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    stats = parse_stats(lines)
    best_distance = max(calculate_distances(stats, FLYING_SECONDS))
    print(best_distance[1], "won with a distance of", best_distance[0], "km")
    points = calculate_points(stats, FLYING_SECONDS)
    print(max(points, key=points.get), "won with", max(points.values()), "points")