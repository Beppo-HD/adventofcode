/* aoc_str.h — string helpers
 */
#ifndef AOC_STR_H
#define AOC_STR_H

#include "aoc_math.h"
#include <stddef.h>
#include <stdbool.h>

[[nodiscard]] char *aoc_strdup(const char *s);
char *str_rstrip(char *s);

bool str_starts_with(const char *s, const char *prefix);
bool str_ends_with(const char *s, const char *suffix);

size_t str_count_char(const char *s, char c);

/* True if `sub` occurs anywhere in s. */
bool str_contains(const char *s, const char *sub);
[[nodiscard]] char **str_split(const char *s, const char *delim, size_t *out_count);
void   str_split_free(char **parts, size_t count);

/* Extract all integers in a string, handling an optional leading '-' 
 * Returns malloc'd array, count out. */
[[nodiscard]] long *str_extract_ints(const char *s, size_t *out_count);

char rotate_letter(char c, int n);
[[nodiscard]] char *str_rotate(const char *s, int n);

typedef struct {
    char  *data;
    size_t len;
    size_t cap;
} StrBuilder;

void  sb_init(StrBuilder *sb);
void  sb_free(StrBuilder *sb);
void  sb_append(StrBuilder *sb, const char *s);
void  sb_append_char(StrBuilder *sb, char c);
void  sb_append_n(StrBuilder *sb, const char *s, size_t n);
/* Returns the built string. Still owned by sb until sb_free(); copy if needed. */
const char *sb_cstr(const StrBuilder *sb);

#endif /* AOC_STR_H */
