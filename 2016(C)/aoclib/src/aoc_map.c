#include "aoc_map.h"
#include "aoc_str.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static unsigned long hash_str(const char *s) {
    /* djb2 */
    unsigned long h = 5381;
    int c;
    while ((c = (unsigned char)*s++)) h = ((h << 5) + h) + (unsigned long)c;
    return h;
}

/* ---- Map (string -> long) ---- */

void map_init(Map *m) {
    m->nbuckets = 16;
    m->buckets = calloc(m->nbuckets, sizeof(MapEntry *));
    m->count = 0;
}

static void map_maybe_grow(Map *m);

void map_free(Map *m) {
    for (size_t i = 0; i < m->nbuckets; i++) {
        MapEntry *e = m->buckets[i];
        while (e) {
            MapEntry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(m->buckets);
    m->buckets = nullptr;
    m->nbuckets = m->count = 0;
}

void map_set(Map *m, const char *key, long value) {
    map_maybe_grow(m);
    unsigned long h = hash_str(key) % m->nbuckets;
    for (MapEntry *e = m->buckets[h]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { e->value = value; return; }
    }
    MapEntry *e = malloc(sizeof(MapEntry));
    e->key = aoc_strdup(key);
    e->value = value;
    e->next = m->buckets[h];
    m->buckets[h] = e;
    m->count++;
}

bool map_get(const Map *m, const char *key, long *out) {
    if (m->nbuckets == 0) return false;
    unsigned long h = hash_str(key) % m->nbuckets;
    for (MapEntry *e = m->buckets[h]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { *out = e->value; return true; }
    }
    return false;
}

bool map_has(const Map *m, const char *key) {
    long tmp;
    return map_get(m, key, &tmp);
}

long map_get_or(const Map *m, const char *key, long def) {
    long out;
    return map_get(m, key, &out) ? out : def;
}

size_t map_count(const Map *m) { return m->count; }

void map_foreach(const Map *m, void (*fn)(const char *, long, void *), void *ctx) {
    for (size_t i = 0; i < m->nbuckets; i++)
        for (MapEntry *e = m->buckets[i]; e; e = e->next)
            fn(e->key, e->value, ctx);
}

static void map_maybe_grow(Map *m) {
    if (m->count < m->nbuckets * 3 / 4) return;
    size_t old_n = m->nbuckets;
    MapEntry **old = m->buckets;
    m->nbuckets *= 2;
    m->buckets = calloc(m->nbuckets, sizeof(MapEntry *));
    for (size_t i = 0; i < old_n; i++) {
        MapEntry *e = old[i];
        while (e) {
            MapEntry *next = e->next;
            unsigned long h = hash_str(e->key) % m->nbuckets;
            e->next = m->buckets[h];
            m->buckets[h] = e;
            e = next;
        }
    }
    free(old);
}

/* ---- PtrMap (string -> void*) ---- */

void ptrmap_init(PtrMap *m) {
    m->nbuckets = 16;
    m->buckets = calloc(m->nbuckets, sizeof(PtrMapEntry *));
    m->count = 0;
}

void ptrmap_free(PtrMap *m, void (*free_value)(void *)) {
    for (size_t i = 0; i < m->nbuckets; i++) {
        PtrMapEntry *e = m->buckets[i];
        while (e) {
            PtrMapEntry *next = e->next;
            if (free_value) free_value(e->value);
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(m->buckets);
    m->buckets = nullptr;
    m->nbuckets = m->count = 0;
}

static void ptrmap_maybe_grow(PtrMap *m) {
    if (m->count < m->nbuckets * 3 / 4) return;
    size_t old_n = m->nbuckets;
    PtrMapEntry **old = m->buckets;
    m->nbuckets *= 2;
    m->buckets = calloc(m->nbuckets, sizeof(PtrMapEntry *));
    for (size_t i = 0; i < old_n; i++) {
        PtrMapEntry *e = old[i];
        while (e) {
            PtrMapEntry *next = e->next;
            unsigned long h = hash_str(e->key) % m->nbuckets;
            e->next = m->buckets[h];
            m->buckets[h] = e;
            e = next;
        }
    }
    free(old);
}

void ptrmap_set(PtrMap *m, const char *key, void *value) {
    ptrmap_maybe_grow(m);
    unsigned long h = hash_str(key) % m->nbuckets;
    for (PtrMapEntry *e = m->buckets[h]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { e->value = value; return; }
    }
    PtrMapEntry *e = malloc(sizeof(PtrMapEntry));
    e->key = aoc_strdup(key);
    e->value = value;
    e->next = m->buckets[h];
    m->buckets[h] = e;
    m->count++;
}

void *ptrmap_get(const PtrMap *m, const char *key) {
    if (m->nbuckets == 0) return nullptr;
    unsigned long h = hash_str(key) % m->nbuckets;
    for (PtrMapEntry *e = m->buckets[h]; e; e = e->next)
        if (strcmp(e->key, key) == 0) return e->value;
    return nullptr;
}

bool ptrmap_has(const PtrMap *m, const char *key) {
    return ptrmap_get(m, key) != nullptr;
}

size_t ptrmap_count(const PtrMap *m) { return m->count; }
