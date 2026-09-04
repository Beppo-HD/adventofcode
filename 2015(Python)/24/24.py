import itertools
import math

FILENAME = "24.txt"


def parse_numbers(lines):
    numbers = []
    for line in lines:
        numbers.append(int(line))
    return numbers


def try_place_number(numbers, used, start_index, remaining_groups, current_sum, target):
    if remaining_groups == 1:
        return True
    if current_sum == target:
        return try_place_number(numbers, used, 0, remaining_groups - 1, 0, target)

    for i in range(start_index, len(numbers)):
        if used[i] or current_sum + numbers[i] > target:
            continue
        used[i] = True
        if try_place_number(numbers, used, i + 1, remaining_groups, current_sum + numbers[i], target):
            return True
        used[i] = False
        if current_sum == 0:
            break
    return False


def can_split_into_groups(numbers, group_count, target):
    numbers = sorted(numbers, reverse=True)
    if not numbers:
        return group_count == 0
    if numbers[0] > target:
        return False
    used = [False] * len(numbers)
    return try_place_number(numbers, used, 0, group_count, 0, target)


def build_groups(numbers, used, groups, start_index, remaining_groups, current_sum, target, group_index):
    if remaining_groups == 1:
        groups[group_index] = [numbers[i] for i in range(len(numbers)) if not used[i]]
        return True
    if current_sum == target:
        return build_groups(numbers, used, groups, 0, remaining_groups - 1, 0, target, group_index + 1)

    for i in range(start_index, len(numbers)):
        if used[i] or current_sum + numbers[i] > target:
            continue
        used[i] = True
        groups[group_index].append(numbers[i])
        if build_groups(numbers, used, groups, i + 1, remaining_groups, current_sum + numbers[i], target, group_index):
            return True
        used[i] = False
        groups[group_index].pop()
        if current_sum == 0:
            break
    return False


def split_into_groups(numbers, group_count, target):
    numbers = sorted(numbers, reverse=True)
    used = [False] * len(numbers)
    groups = [[] for _ in range(group_count)]

    if build_groups(numbers, used, groups, 0, group_count, 0, target, 0):
        return groups
    return None


def find_valid_partition(numbers, num_groups):
    total = sum(numbers)
    if total % num_groups != 0:
        return None
    target = total // num_groups

    best_candidates = []
    for group_size in range(1, len(numbers) - (num_groups - 1) + 1):
        candidates = []
        for combo in itertools.combinations(numbers, group_size):
            if sum(combo) != target:
                continue
            remainder = [x for x in numbers if x not in set(combo)]
            if can_split_into_groups(remainder, num_groups - 1, target):
                candidates.append(combo)
        if candidates:
            best_candidates = candidates
            break

    if not best_candidates:
        return None

    first_group = min(best_candidates, key=lambda c: math.prod(c))
    remainder = [x for x in numbers if x not in set(first_group)]
    other_groups = split_into_groups(remainder, num_groups - 1, target)

    return [sorted(first_group)] + [sorted(g) for g in other_groups]


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    numbers = parse_numbers(lines)

    for groupings in [3, 4]:
        groups = find_valid_partition(numbers, groupings)
        print(f"Entanglement for smallest of {groupings} groups:", math.prod(groups[0]))