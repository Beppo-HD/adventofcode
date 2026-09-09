#include "aoc_str.h"
#include "aoc_io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_abba(char *s){
    return s[0] == s[3] && s[0] != s[1] && s[1] == s[2];
}

bool contains_abba(char *s){
    for(size_t i = 0; i + 3 < strlen(s); i++){
        if(is_abba(&s[i])) return true;
    }
    return false;
}

bool supports_TLS(char **parts, size_t part_count){
    bool abba_in_brackets = false, abba_outside_brackets = false;
    for(size_t j = 0; j < part_count; j++){
        bool contains = contains_abba(parts[j]);
        if(contains){
            if(j % 2 == 0){
                abba_outside_brackets = true;
            }else{
                abba_in_brackets = true;
            }
        }
    }
    return !abba_in_brackets && abba_outside_brackets;
}

bool is_aba(char *s) {
    return s[0] == s[2] && s[0] != s[1];
}

bool supports_SSL(char **parts, size_t part_count) {
    for (size_t j = 0; j < part_count; j += 2) {
        char *part = parts[j];
        size_t len = strlen(part);

        for (size_t i = 0; i + 2 < len; i++) {
            if (is_aba(&part[i])) {
                char bab[4] = { part[i+1], part[i], part[i+1], '\0' };

                for (size_t k = 1; k < part_count; k += 2) {
                    if (str_contains(parts[k], bab)) return true;
                }
            }
        }
    }
    return false;
}

int main(void) {
    Lines l = read_lines("input.txt");
    int TLS_count = 0;
    int SSL_count = 0;

    for(size_t i = 0; i < l.count; i++){
        size_t part_count;
        char **parts = str_split_any(l.lines[i], "[]", &part_count);
        
        TLS_count += supports_TLS(parts, part_count) ? 1 : 0;
        SSL_count += supports_SSL(parts, part_count) ? 1 : 0;
        str_split_free(parts, part_count);
    }

    printf("Amount of IPs that support TLS: %d\n", TLS_count);
    printf("Amount of IPs that support SSL: %d\n", SSL_count);


    free_lines(&l);
    return 0;
}
