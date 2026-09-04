FILENAME = "17.txt"

def parse_containers(lines):
    containers = []
    for line in lines:
        containers.append(int(line))
    return containers

def find_subsets_sum_to_x(nums, x):
    nums.sort()
    result = []

    def backtrack(index, current_sum, current_subset):
        if current_sum == x:
            result.append(list(current_subset))
            return
        if current_sum > x or index >= len(nums):
            return
        for i in range(index, len(nums)):
            current_subset.append(nums[i])
            backtrack(i + 1, current_sum + nums[i], current_subset)
            current_subset.pop()
    backtrack(0, 0, [])
    return result

if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    valid_combinations = find_subsets_sum_to_x(parse_containers(lines), 150)
    print("Valid combinations to fit 150 litres:", len(valid_combinations))
    shortest = 100
    for combination in valid_combinations:
        shortest = (len(combination) if len(combination) < shortest else shortest)
    smallest_combinations = []
    for combination in valid_combinations:
        if len(combination) == shortest:
            smallest_combinations.append(combination)
    print("Combinations with least amount of containers:", len(smallest_combinations))