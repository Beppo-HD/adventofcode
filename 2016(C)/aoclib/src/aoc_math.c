#include "aoc_math.h"
#include <stdlib.h>

long aoc_mod(long a, long m) {
    long r = a % m;
    return r < 0 ? r + (m < 0 ? -m : m) : r;
}
