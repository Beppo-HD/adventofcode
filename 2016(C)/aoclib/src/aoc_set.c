#include "aoc_set.h"
#include "aoc_str.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static unsigned long hash_pair(long x, long y) {
    unsigned long h = 146527;
    h = h * 31 + (unsigned long)x;
    h = h * 31 + (unsigned long)y;
    return h;
}

void pairset_init(PairSet *s) {
    s->nbuckets = 16;
    s->buckets = calloc(s->nbuckets, sizeof(PairSetEntry *));
    s->count = 0;
}

void pairset_free(PairSet *s) {
    for (size_t i = 0; i < s->nbuckets; i++) {
        PairSetEntry *e = s->buckets[i];
        while (e) {
            PairSetEntry *next = e->next;
            free(e);
            e = next;
        }
    }
    free(s->buckets);
    s->buckets = nullptr;
    s->nbuckets = s->count = 0;
}

static void pairset_maybe_grow(PairSet *s) {
    if (s->count < s->nbuckets * 3 / 4) return;
    size_t old_n = s->nbuckets;
    PairSetEntry **old = s->buckets;
    s->nbuckets *= 2;
    s->buckets = calloc(s->nbuckets, sizeof(PairSetEntry *));
    for (size_t i = 0; i < old_n; i++) {
        PairSetEntry *e = old[i];
        while (e) {
            PairSetEntry *next = e->next;
            unsigned long h = hash_pair(e->x, e->y) % s->nbuckets;
            e->next = s->buckets[h];
            s->buckets[h] = e;
            e = next;
        }
    }
    free(old);
}

bool pairset_contains(const PairSet *s, long x, long y) {
    if (s->nbuckets == 0) return false;
    unsigned long h = hash_pair(x, y) % s->nbuckets;
    for (PairSetEntry *e = s->buckets[h]; e; e = e->next)
        if (e->x == x && e->y == y) return true;
    return false;
}

void pairset_add(PairSet *s, long x, long y) {
    if (pairset_contains(s, x, y)) return;
    pairset_maybe_grow(s);
    unsigned long h = hash_pair(x, y) % s->nbuckets;
    PairSetEntry *e = malloc(sizeof(PairSetEntry));
    e->x = x; e->y = y;
    e->next = s->buckets[h];
    s->buckets[h] = e;
    s->count++;
}

size_t pairset_count(const PairSet *s) { return s->count; }
