FILENAME = "7.txt"

cables_dict = {}
def cables_parse(s):
    for line in s:
        pieces = line.split(" ")
        amount_pieces = len(pieces)
        cable_one = cable_two = operation = cable_out = None
        if amount_pieces == 3:
            cable_one, _, cable_out = pieces
        elif amount_pieces == 4:
            operation, cable_one, _, cable_out = pieces
        else:
            cable_one, operation, cable_two, _, cable_out = pieces
        cables_dict[cable_out] = (operation, cable_one, cable_two)

cache = {}
def solve(cable):
    if cable.isdigit():
        return int(cable)
        
    if cable in cache:
        return cache[cable]
    
    state = cables_dict[cable]
    op = None
    match state[0]:
        case "NOT":
            op = lambda x, y: ~int(solve(x))
        case "RSHIFT":
            op = lambda x, y: int(solve(x)) >> int(solve(y))
        case "LSHIFT":
            op = lambda x, y: int(solve(x)) << int(solve(y))
        case "AND":
            op = lambda x, y: int(solve(x)) & int(solve(y))
        case "OR":
            op = lambda x, y: int(solve(x)) | int(solve(y))
        case None:
            op = lambda x, y: int(solve(x))
    result = op(state[1], state[2]) & 0xFFFF
    cache[cable] = result
    return result


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    cables_parse(lines)
    a = solve("a")
    print("Cable 'a':", a)
    cache.clear()
    cables_dict['b'] = (None, str(a), None)
    print("Cable 'a' when 'b' stats at", a, ":",  solve("a"))