import itertools

FILENAME = "input.txt"
PLAYER_HP = 100

SHOP = {
    "Weapons":{
        "Dagger":[8, 4, 0], 
        "Shortword":[10, 5, 0],
        "Warhammer":[25, 6, 0],
        "Longsword":[40, 7, 0],
        "Greataxe":[74, 8, 0]
    },
    "Armor":{
        "Leather":[13, 0, 1],
        "Chainmail":[31, 0, 2],
        "Splintmail":[53, 0, 3],
        "Bandedmail":[75, 0, 4],
        "Platemail":[102, 0, 5],
    },
    "Rings":{
        "Damage +1":[25, 1, 0],
        "Damage +2":[50, 2, 0],
        "Damage +3":[100, 3, 0],
        "Defense +1":[20, 0, 1],
        "Defense +2":[40, 0, 2],
        "Defense +3":[80, 0, 3],
    }
}

def parse_boss_stats(lines):
    stats = []
    for line in lines:
        stats.append(int(line.split()[-1]))
    return stats

def find_all_loadouts():
    armor_options = [None] + list(SHOP["Armor"].items())
    ring_options = [()] + list(itertools.combinations(list(SHOP["Rings"].items()), 1)) + list(itertools.combinations(list(SHOP["Rings"].items()), 2))
    return list(itertools.product(list(SHOP["Weapons"].items()), armor_options, ring_options))

def calculate_stats(loadout):
    weapon, armor, rings = loadout
    items = [weapon]
    if armor is not None:
        items.append(armor)
    items.extend(rings)

    total_cost = sum(item[1][0] for item in items)
    total_damage = sum(item[1][1] for item in items)
    total_armor = sum(item[1][2] for item in items)
    return PLAYER_HP, total_damage, total_armor, int(total_cost)

def fight(player_stats, enemy_stats):
    def hit(damage, entity):
        return (entity[0] - max(1, damage - entity[2]), entity[1], entity[2])

    while player_stats[0] > 0 and enemy_stats[0] > 0:
        enemy_stats = hit(player_stats[1], enemy_stats)
        if enemy_stats[0] <= 0:
            return "Win"
        player_stats = hit(enemy_stats[1], player_stats)
        if player_stats[0] <= 0:
            return "Loss"

def find_loadout(enemy_stats, best = True):
    valid_loadouts = []
    best_cost = None
    for loadout in find_all_loadouts():
        stats = calculate_stats(loadout)
        if fight(stats, enemy_stats) == ("Win" if best else "Loss"):
            valid_loadouts.append(loadout)
            stats = calculate_stats(loadout)
            if best_cost is None or ((stats[3] < best_cost) if best else (stats[3] > best_cost)):
                best_cost = stats[3]
    return best_cost

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Lowest cost for Win:", find_loadout(parse_boss_stats(lines)))
    print("Highest cost for Loss", find_loadout(parse_boss_stats(lines), False))