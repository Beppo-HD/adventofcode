#include "aoc_str.h"
#include "aoc_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t parse_marker(char *s, size_t i, long *a, long *b) {
    size_t close = i;
    while (s[close] != ')') close++;

    size_t marker_len = close - i - 1;
    char marker[32];
    memcpy(marker, s + i + 1, marker_len);
    marker[marker_len] = '\0';

    size_t n;
    long *nums = str_extract_ints(marker, &n);
    *a = nums[0];
    *b = nums[1];
    free(nums);

    return close;
}

char *decompress(char *s) {
    StrBuilder sb;
    sb_init(&sb);

    size_t len = strlen(s);
    size_t i = 0;
    while (i < len) {
        if (s[i] == '(') {
            long a, b;
            size_t close = parse_marker(s, i, &a, &b);

            size_t repeat_start = close + 1;
            for (long rep = 0; rep < b; rep++) {
                sb_append_n(&sb, s + repeat_start, (size_t)a);
            }

            i = repeat_start + (size_t)a;
        } else {
            sb_append_char(&sb, s[i]);
            i++;
        }
    }

    char *result = aoc_strdup(sb_cstr(&sb));
    sb_free(&sb);
    return result;
}

long long twice_decompressed_length(char *s, size_t start, size_t end) {
    long long total = 0;
    size_t i = start;

    while (i < end) {
        if (s[i] == '(') {
            long a, b;
            size_t close = parse_marker(s, i, &a, &b);

            size_t repeat_start = close + 1;
            size_t repeat_end = repeat_start + (size_t)a;

            total += twice_decompressed_length(s, repeat_start, repeat_end) * (long long)b;
            i = repeat_end;
        } else {
            total++;
            i++;
        }
    }

    return total;
}

int main(void) {
    Lines l = read_lines("input.txt");
    char *decompressed = decompress(l.lines[0]);
    printf("File length after decompression: %lld\n", strlen(decompressed));
    free(decompressed);

    printf("File length after decompression v.2: %lld\n", twice_decompressed_length(l.lines[0], 0, strlen(l.lines[0])));
    
    free_lines(&l);
    return 0;
}
