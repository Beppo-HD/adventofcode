FILENAME = "input.txt"

class PairTracker:
    def __init__(self):
        self._pairs = set()

    def add(self, a, b):
        self._pairs.add((a, b))

    def count(self):
        return len(self._pairs)

    def __contains__(self, pair):
        return pair in self._pairs

    def __iter__(self):
        return iter(self._pairs)
    

def houses_solo(s):
    tracker = PairTracker()
    x = y = 0
    for cur in s:
        match cur:
            case '<':
                x -= 1
            case '>':
                x += 1
            case '^':
                y += 1
            case 'v':
                y -= 1
        tracker.add(x, y)
    return tracker.count()


def houses_duo(s):
    tracker = PairTracker()
    x = [0, 0]
    y = [0, 0]
    turn = 0
    for cur in s:
        match cur:
            case '<':
                x[turn] -= 1
            case '>':
                x[turn] += 1
            case '^':
                y[turn] += 1
            case 'v':
                y[turn] -= 1
        tracker.add(x[turn], y[turn])
        turn = 1 if turn == 0 else 0
    return tracker.count()


if __name__ == "__main__":
    with open(FILENAME) as f_in:
        lines = [line.rstrip() for line in f_in if line.strip()]
    print("Visited alone:", houses_solo(lines[0]))
    print("Visited together:", houses_duo(lines[0]))