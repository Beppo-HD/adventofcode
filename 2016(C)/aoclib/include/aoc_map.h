/* aoc_map.h — string-keyed hash map
 *
 * Two flavors are provided:
 *   Map      — string key -> long value      (counts, memo caches, tallies)
 *   PtrMap   — string key -> void* value     (nested structures, e.g. a
 *                                              Map* per key, for "dict of
 *                                              dicts" patterns)
 */
#ifndef AOC_MAP_H
#define AOC_MAP_H

#include <stddef.h>
#include <stdbool.h>

/* ---- Map: string -> long ---- */
typedef struct MapEntry {
    char *key;
    long  value;
    struct MapEntry *next;
} MapEntry;

typedef struct {
    MapEntry **buckets;
    size_t     nbuckets;
    size_t     count;
} Map;

void map_init(Map *m);
void map_free(Map *m);
void map_set(Map *m, const char *key, long value);
/* Returns true and writes *out if found, else returns false and leaves *out untouched. */
bool map_get(const Map *m, const char *key, long *out);
bool map_has(const Map *m, const char *key);
/* Convenience: get value, or `def` if key not present. */
long map_get_or(const Map *m, const char *key, long def);
size_t map_count(const Map *m);
/* Iterate all entries: calls fn(key, value, ctx) for each. Order is unspecified. */
void map_foreach(const Map *m, void (*fn)(const char *key, long value, void *ctx), void *ctx);

/* ---- PtrMap: string -> void* ---- */
typedef struct PtrMapEntry {
    char *key;
    void *value;
    struct PtrMapEntry *next;
} PtrMapEntry;

typedef struct {
    PtrMapEntry **buckets;
    size_t        nbuckets;
    size_t        count;
} PtrMap;

void  ptrmap_init(PtrMap *m);
/* If free_values is non-null, it is called on every stored value during ptrmap_free. */
void  ptrmap_free(PtrMap *m, void (*free_value)(void *));
void  ptrmap_set(PtrMap *m, const char *key, void *value);
void *ptrmap_get(const PtrMap *m, const char *key); /* nullptr if absent */
bool  ptrmap_has(const PtrMap *m, const char *key);
size_t ptrmap_count(const PtrMap *m);

#endif /* AOC_MAP_H */
