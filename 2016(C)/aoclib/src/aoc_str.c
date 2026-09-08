#include "aoc_str.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *aoc_strdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *out = malloc(n);
    memcpy(out, s, n);
    return out;
}

char *str_rstrip(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (isspace((unsigned char)s[len - 1]) || s[len - 1] == '\r' || s[len - 1] == '\n'))
        len--;
    s[len] = '\0';
    return s;
}

bool str_starts_with(const char *s, const char *prefix) {
    size_t lp = strlen(prefix);
    return strncmp(s, prefix, lp) == 0;
}

bool str_ends_with(const char *s, const char *suffix) {
    size_t ls = strlen(s), lf = strlen(suffix);
    if (lf > ls) return false;
    return strcmp(s + (ls - lf), suffix) == 0;
}

size_t str_count_char(const char *s, char c) {
    size_t n = 0;
    for (; *s; s++) if (*s == c) n++;
    return n;
}

bool str_contains(const char *s, const char *sub) {
    return strstr(s, sub) != nullptr;
}

char **str_split(const char *s, const char *delim, size_t *out_count) {
    size_t dl = strlen(delim);
    size_t cap = 8, n = 0;
    char **parts = malloc(cap * sizeof(char *));

    if (dl == 0) {
        /* split into individual characters */
        size_t sl = strlen(s);
        parts = realloc(parts, sl * sizeof(char *));
        for (size_t i = 0; i < sl; i++) {
            char *one = malloc(2);
            one[0] = s[i]; one[1] = '\0';
            parts[i] = one;
        }
        *out_count = sl;
        return parts;
    }

    const char *start = s;
    const char *p;
    while ((p = strstr(start, delim)) != nullptr) {
        size_t len = (size_t)(p - start);
        char *piece = malloc(len + 1);
        memcpy(piece, start, len);
        piece[len] = '\0';
        if (n == cap) { cap *= 2; parts = realloc(parts, cap * sizeof(char *)); }
        parts[n++] = piece;
        start = p + dl;
    }
    /* remainder */
    char *piece = aoc_strdup(start);
    if (n == cap) { cap *= 2; parts = realloc(parts, cap * sizeof(char *)); }
    parts[n++] = piece;

    *out_count = n;
    return parts;
}

void str_split_free(char **parts, size_t count) {
    for (size_t i = 0; i < count; i++) free(parts[i]);
    free(parts);
}

long *str_extract_ints(const char *s, size_t *out_count) {
    size_t cap = 8, n = 0;
    long *out = malloc(cap * sizeof(long));
    const char *p = s;
    while (*p) {
        int neg = 0;
        if (*p == '-' && isdigit((unsigned char)p[1])) { neg = 1; p++; }
        if (isdigit((unsigned char)*p)) {
            long val = 0;
            while (isdigit((unsigned char)*p)) {
                val = val * 10 + (*p - '0');
                p++;
            }
            if (neg) val = -val;
            if (n == cap) { cap *= 2; out = realloc(out, cap * sizeof(long)); }
            out[n++] = val;
        } else {
            p++;
        }
    }
    *out_count = n;
    return out;
}

char rotate_letter(char c, int n) {
    if (c >= 'a' && c <= 'z') return (char)('a' + aoc_mod(c - 'a' + n, 26));
    if (c >= 'A' && c <= 'Z') return (char)('A' + aoc_mod(c - 'A' + n, 26));
    return c;
}

char *str_rotate(const char *s, int n) {
    size_t len = strlen(s);
    char *out = malloc(len + 1);
    for (size_t i = 0; i < len; i++) out[i] = rotate_letter(s[i], n);
    out[len] = '\0';
    return out;
}

void sb_init(StrBuilder *sb) {
    sb->cap = 32;
    sb->len = 0;
    sb->data = malloc(sb->cap);
    sb->data[0] = '\0';
}

void sb_free(StrBuilder *sb) {
    free(sb->data);
    sb->data = nullptr;
    sb->len = sb->cap = 0;
}

static void sb_ensure(StrBuilder *sb, size_t extra) {
    if (sb->len + extra + 1 <= sb->cap) return;
    size_t new_cap = sb->cap * 2;
    while (new_cap < sb->len + extra + 1) new_cap *= 2;
    sb->data = realloc(sb->data, new_cap);
    sb->cap = new_cap;
}

void sb_append_n(StrBuilder *sb, const char *s, size_t n) {
    sb_ensure(sb, n);
    memcpy(sb->data + sb->len, s, n);
    sb->len += n;
    sb->data[sb->len] = '\0';
}

void sb_append(StrBuilder *sb, const char *s) {
    sb_append_n(sb, s, strlen(s));
}

const char *sb_cstr(const StrBuilder *sb) {
    return sb->data;
}