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
