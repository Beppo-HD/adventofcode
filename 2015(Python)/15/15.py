import itertools

FILENAME = "15.txt"

def parse_ingredient_stats(lines):
    stats = []
    for line in lines:
        name, _, cap, _, dur, _, flv, _, tex, _, cal = line.split(" ")
        stats.append((name[:-1], cap[:-1], dur[:-1], flv[:-1], tex[:-1], cal))
    return stats

def check_recipe(stats, combination):
    totals = [0, 0, 0, 0, 0]
    for amount, stat in zip(combination, stats):
        properties = stat[1:]
        for idx in range(len(properties)):
            totals[idx] += int(properties[idx]) * int(amount)
    total = 1
    for val in totals[:4]:
        total *= max(val, 0)

    return (total, totals[4])

def find_best_recipe(stats, calories = None):
    permutations = []
    for i in range(101):
        for j in range(101 - i):
            for k in range(101 - i - j):
                l = 100 - i - j - k
                permutations.append((i, j, k, l))
    best_recipe_score = (0, None)
    for combination in permutations:
        current_score = check_recipe(stats, combination)
        best_recipe_score = ((current_score[0], combination) if current_score[0] > best_recipe_score[0] and (calories is None or calories == current_score[1]) else best_recipe_score)
    return best_recipe_score

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    ingredients = parse_ingredient_stats(lines)
    best_recipe = find_best_recipe(ingredients)
    print("Best recipe values:", best_recipe[1], "giving a total score of:", best_recipe[0])
    best_recipe = find_best_recipe(ingredients, 500)
    print("Best recipe values for 500 calories:", best_recipe[1], "giving a total score of:", best_recipe[0])