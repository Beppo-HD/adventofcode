import math

FILENAME = "20.txt"

def find_divisors(n):
    divisors = set()
    if n <= 0:
        return divisors
    for i in range(1, int(math.isqrt(n)) + 1):
        if n % i == 0:
            divisors.add(i)
            divisors.add(n // i)
    return divisors

def calculate_present_amount(house_nr, unionized=False):
    elves = find_divisors(house_nr)
    presents = 0
    for elf in elves:
        if unionized:
            if house_nr / elf <= 50:
                presents += 11 * elf
        else:
            presents += 10 * elf
    return presents

def find_first_house_above(n, unionized=False):
    i = 0
    while calculate_present_amount(i, unionized) < n:
        i += 1
    return i

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("First house with at least as many presents:", find_first_house_above(int(lines[0])))
    print("First house after elves unionized:", find_first_house_above(int(lines[0]), True))