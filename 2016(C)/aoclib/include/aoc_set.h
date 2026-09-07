/* aoc_set.h — hash sets.
 */
#ifndef AOC_SET_H
#define AOC_SET_H

#include <stddef.h>
#include <stdbool.h>

/* ---- PairSet: set of (long, long) pairs ---- */
typedef struct PairSetEntry {
    long x, y;
    struct PairSetEntry *next;
} PairSetEntry;

typedef struct {
    PairSetEntry **buckets;
    size_t         nbuckets;
    size_t         count;
} PairSet;

void   pairset_init(PairSet *s);
void   pairset_free(PairSet *s);
void   pairset_add(PairSet *s, long x, long y);
bool   pairset_contains(const PairSet *s, long x, long y);
size_t pairset_count(const PairSet *s);

#endif /* AOC_SET_H */
