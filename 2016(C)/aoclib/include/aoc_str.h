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

[[nodiscard]] char *int_to_string(int x);
[[nodiscard]] char *uint_to_string(unsigned int x);
[[nodiscard]] char *long_to_string(long x);
[[nodiscard]] char *ulong_to_string(unsigned long x);
[[nodiscard]] char *longlong_to_string(long long x);
[[nodiscard]] char *ulonglong_to_string(unsigned long long x);
[[nodiscard]] char *double_to_string(double x);
[[nodiscard]] char *float_to_string(float x);
[[nodiscard]] char *char_to_string(char c);
[[nodiscard]] char *bool_to_string(bool b);
[[nodiscard]] char *cstr_to_string(const char *s);

#define to_string(x) _Generic((x), \
    bool:               bool_to_string, \
    char:               char_to_string, \
    signed char:        int_to_string, \
    unsigned char:      uint_to_string, \
    short:              int_to_string, \
    unsigned short:     uint_to_string, \
    int:                int_to_string, \
    unsigned int:       uint_to_string, \
    long:               long_to_string, \
    unsigned long:      ulong_to_string, \
    long long:          longlong_to_string, \
    unsigned long long: ulonglong_to_string, \
    float:              float_to_string, \
    double:             double_to_string, \
    char *:             cstr_to_string, \
    const char *:       cstr_to_string \
)(x)

#endif /* AOC_STR_H */
