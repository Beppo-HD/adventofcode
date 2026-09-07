/* aoc_str.h — string helpers
 */
#ifndef AOC_STR_H
#define AOC_STR_H

#include <stddef.h>
#include <stdbool.h>

[[nodiscard]] char *aoc_strdup(const char *s);
char *str_rstrip(char *s);

bool str_starts_with(const char *s, const char *prefix);
bool str_ends_with(const char *s, const char *suffix);

/* True if `sub` occurs anywhere in s. */
bool str_contains(const char *s, const char *sub);
[[nodiscard]] char **str_split(const char *s, const char *delim, size_t *out_count);
void   str_split_free(char **parts, size_t count);

/* Extract all integers in a string, handling an optional leading '-' 
 * Returns malloc'd array, count out. */
[[nodiscard]] long *str_extract_ints(const char *s, size_t *out_count);

#endif /* AOC_STR_H */
