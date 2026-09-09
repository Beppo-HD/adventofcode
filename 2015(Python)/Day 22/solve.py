FILENAME = "input.txt"
Start_Stats = {
    "Player":{
        "hp":50,
        "armor":0,
        "mana":500,
        "damage":0
    },
    "Boss":{
        "hp":0,
        "armor":0,
        "mana":0,
        "damage":0
    }
}

Ancient_Codex = { 
    "Magic Missile":{
        "mana_cost":53,
        "duration":1,
        "damage":4,
        "mana_gain":0,
        "health_gain":0,
        "armor":0
    },
    "Drain":{
        "mana_cost":73, 
        "duration":1, 
        "damage":2, 
        "mana_gain":0, 
        "health_gain":2, 
        "armor":0
    },
    "Shield":{
        "mana_cost":113, 
        "duration":6, 
        "damage":0, 
        "mana_gain":0, 
        "health_gain":0, 
        "armor":7
    },
    "Poison":{
        "mana_cost":173, 
        "duration":6, 
        "damage":3, 
        "mana_gain":0, 
        "health_gain":0, 
        "armor":0
    },
    "Recharge":{
        "mana_cost":229, 
        "duration":5, 
        "damage":0, 
        "mana_gain":101, 
        "health_gain":0, 
        "armor":0
    }
}

BEST_MANA = float('inf')

def parse_boss_stats(lines):
    for stat, line in zip(["hp", "damage"], lines):
        Start_Stats["Boss"][stat] = int(line.split()[-1])

def tick_magic(current_stats, active_spells):
    new_active_spells = []
    stats = {
        "hp":current_stats["hp"], 
        "armor":0, 
        "mana":current_stats["mana"], 
        "damage":0
    }
    for spell, duration in active_spells:
        spell_stats = Ancient_Codex[spell]
        stats["hp"] += spell_stats["health_gain"]
        stats["armor"] += spell_stats["armor"]
        stats["mana"] += spell_stats["mana_gain"]
        stats["damage"] += spell_stats["damage"]
        new_duration = duration - 1
        if new_duration > 0:
            new_active_spells.append((spell, new_duration))
    return stats, new_active_spells

def hit(damage, entity):
        if damage <= 0:
            return entity
        return {**entity, "hp":entity["hp"] - max(1, damage - entity["armor"])}

def check_game_over(player_stats, enemy_stats, mana_spent):
    global BEST_MANA
    if enemy_stats["hp"] <= 0:
        BEST_MANA = min(BEST_MANA, mana_spent)
        return True
    if player_stats["hp"] <= 0:
        return True
    return False

def player_turn(player_stats, enemy_stats, active_spells, mana_spent, hard_mode=False):
    global BEST_MANA
    if hard_mode:
        player_stats["hp"] -= 1
    player_stats, active_spells = tick_magic(player_stats, active_spells)
    enemy_stats = hit(player_stats["damage"], enemy_stats)
    if(check_game_over(player_stats, enemy_stats, mana_spent)):
        return
    
    already_active = {spell for spell, _ in active_spells}
    for spell, effect in Ancient_Codex.items():
        if spell in already_active or player_stats["mana"] < effect["mana_cost"]:
            continue
        new_mana_spent = mana_spent + effect["mana_cost"]
        if new_mana_spent >= BEST_MANA:
            continue
        new_active_spells = active_spells + [(spell, effect["duration"])]
        new_player_stats = {**player_stats, "mana":player_stats["mana"] - effect["mana_cost"]}
        enemy_turn(new_player_stats, enemy_stats, new_active_spells, new_mana_spent, hard_mode)

def enemy_turn(player_stats, enemy_stats, active_spells, mana_spent, hard_mode):
    player_stats, active_spells = tick_magic(player_stats, active_spells)
    enemy_stats = hit(player_stats["damage"], enemy_stats)
    if(check_game_over(player_stats, enemy_stats, mana_spent)):
        return
    player_stats = hit(enemy_stats["damage"], player_stats)
    if (check_game_over(player_stats, enemy_stats, mana_spent)):
        return
    
    player_turn(player_stats, enemy_stats, active_spells, mana_spent, hard_mode)

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    parse_boss_stats(lines)
    player_turn(Start_Stats["Player"], Start_Stats["Boss"], [], 0)
    print("Least amount of mana to win:", BEST_MANA)
    BEST_MANA = float('inf')
    player_turn(Start_Stats["Player"], Start_Stats["Boss"], [], 0, True)
    print("Least amount of mana to win in hard mode:", BEST_MANA)