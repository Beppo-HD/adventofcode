#include "aoc_str.h"
#include "aoc_io.h"
#include "aoc_md5.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_n_zeros(char *s, int n){
    for(int i = 0; i < n; i++) if(s[i] != '0') return false;
    return true;
}

int main(void) {
    Lines l = read_lines("input.txt");
    char *door_id = l.lines[0];

    char *password = calloc(9, sizeof(char));
    char *harder_password = calloc(9, sizeof(char));
    int i = 0, password_len = 0, harder_password_len = 0;
    bool filled[8] = { false };
    while(password_len < 8 || harder_password_len < 8){
        char to_hex[64];
        snprintf(to_hex, sizeof(to_hex), "%s%d", door_id, i);
        char hex[33];
        md5_hex(to_hex, strlen(to_hex), hex);
        if(check_n_zeros(hex, 5)){
            if(password_len < 8){
                password[password_len] = hex[5];
                password_len++;
            }
            if(harder_password_len < 8){
                if((hex[5] >= '0' && hex[5] <= '7')){
                    int pos = hex[5] - '0';
                    if(!filled[pos]){
                        harder_password[pos] = hex[6];
                        filled[pos] = true;
                        harder_password_len++;
                    }
                }
            }
        }
        i++;
    }
    
    printf("Password for first door: %s\n", password);
    printf("Password for second door: %s\n", harder_password);

    free(password);
    free(harder_password);
    free_lines(&l);
    return 0;
}
