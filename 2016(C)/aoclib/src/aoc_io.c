#define _POSIX_C_SOURCE 200809L
#include "aoc_io.h"
#include "aoc_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static bool read_one_line(char **buf, size_t *bufcap, FILE *f) {
    if (*bufcap == 0) {
        *bufcap = 128;
        *buf = malloc(*bufcap);
    }
    (*buf)[0] = '\0';
    size_t len = 0;
    for (;;) {
        if (len + 2 > *bufcap) {
            *bufcap *= 2;
            *buf = realloc(*buf, *bufcap);
        }
        if (!fgets(*buf + len, (int)(*bufcap - len), f)) {
            return len > 0; /* true if we read something before EOF */
        }
        len += strlen(*buf + len);
        if (len > 0 && (*buf)[len - 1] == '\n') return true;
        if (feof(f)) return true;
    }
}

Lines read_lines(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "aoclib: could not open '%s': %s\n", filename, strerror(errno));
        exit(1);
    }

    size_t cap = 16, n = 0;
    char **lines = malloc(cap * sizeof(char *));

    char *buf = nullptr;
    size_t bufcap = 0;
    while (read_one_line(&buf, &bufcap, f)) {
        char *copy = aoc_strdup(buf);
        str_rstrip(copy);
        if (copy[0] == '\0') { /* blank after stripping -> skip */
            free(copy);
            continue;
        }
        if (n == cap) { cap *= 2; lines = realloc(lines, cap * sizeof(char *)); }
        lines[n++] = copy;
    }
    free(buf);
    fclose(f);

    Lines result = { lines, n };
    return result;
}

void free_lines(Lines *l) {
    for (size_t i = 0; i < l->count; i++) free(l->lines[i]);
    free(l->lines);
    l->lines = nullptr;
    l->count = 0;
}

char *read_file(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "aoclib: could not open '%s'\n", filename);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((size_t)size + 1);
    size_t read = fread(buf, 1, (size_t)size, f);
    buf[read] = '\0';
    fclose(f);
    return buf;
}
