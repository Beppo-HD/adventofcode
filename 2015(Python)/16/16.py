FILENAME = "16.txt"
INFO = {"children":3, "cats":7, "samoyeds":2, "pomeranians":3, "akitas":0, "vizslas":0, "goldfish":5, "trees":3, "cars":2, "perfumes":1}

def parse_aunts(lines):
    aunts = {}
    for line in lines:
        _, aunt_nr, first, first_val, second, second_val, third, third_val = line.split(" ")
        aunts[aunt_nr[:-1]] = {first[:-1]:int(first_val[:-1]), second[:-1]:int(second_val[:-1]), third[:-1]:int(third_val)}
    return aunts

def find_aunt(aunts, ranges=False):
    for aunt_nr, properties in aunts.items():
        discrepancy = False
        for val in INFO:
            if val not in properties:
                continue
            if ranges and val in ["cats", "trees", "pomeranians", "goldfish"]:
                if val in ["cats", "trees"]:
                    if properties[val] <= INFO[val]:
                        discrepancy = True
                if val in ["pomeranians", "goldfish"]:
                    if properties[val] >= INFO[val]:
                        discrepancy = True
                        break
            elif properties[val] != INFO[val]:
                discrepancy = True
                break
        if not discrepancy:
            return aunt_nr
        

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Suspected aunt:", find_aunt(parse_aunts(lines)))
    print("Actual aunt:", find_aunt(parse_aunts(lines), True))