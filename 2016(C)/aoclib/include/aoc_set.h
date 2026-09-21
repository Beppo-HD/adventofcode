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

/* ---- StrSet: set of strings ---- */
typedef struct StrSetEntry {
    char *key;
    struct StrSetEntry *next;
} StrSetEntry;

typedef struct {
    StrSetEntry **buckets;
    size_t        nbuckets;
    size_t        count;
} StrSet;

void   strset_init(StrSet *s);
void   strset_free(StrSet *s);
void   strset_add(StrSet *s, const char *key);
bool   strset_contains(const StrSet *s, const char *key);
size_t strset_count(const StrSet *s);

#endif /* AOC_SET_H */
