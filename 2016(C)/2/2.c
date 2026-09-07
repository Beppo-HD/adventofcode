#include "aoc_io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char find_keypad_at(int x, int y){
    static const char keypad[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    return keypad[y][x];
}

char find_strange_keypad_at(int x, int y){
    static const char strange_keypad[5][5] = {
        {'0', '0', '1', '0', '0'},
        {'0', '2', '3', '4', '0'},
        {'5', '6', '7', '8', '9'},
        {'0', 'A', 'B', 'C', '0'},
        {'0', '0', 'D', '0', '0'}
    }; 
    return strange_keypad[y + 2][x + 2];
}

void follow_steps(Lines *l, int *cur_x, int *cur_y, char *code, bool strange){
    for(size_t i = 0; i < l->count; i++){
        for(int j = 0; l->lines[i][j] != '\0'; j++){
            if(!strange){
                switch(l->lines[i][j]){
                    case 'D':{
                        if(*cur_y < 2) *cur_y += 1;
                        break;
                    }
                    case 'U':{
                        if(*cur_y > 0) *cur_y -= 1;
                        break;
                    }
                    case 'R':{
                        if(*cur_x < 2) *cur_x += 1;
                        break;
                    }
                    case 'L':{
                        if(*cur_x > 0) *cur_x -= 1;
                        break;
                    }
                }
            }else{
                switch(l->lines[i][j]){
                    case 'D':{
                        if((abs(*cur_y + 1) + abs(*cur_x)) <= 2) *cur_y += 1;
                        break;
                    }
                    case 'U':{
                        if((abs(*cur_y - 1) + abs(*cur_x)) <= 2) *cur_y -= 1;
                        break;
                    }
                    case 'R':{
                        if((abs(*cur_y) + abs(*cur_x + 1)) <= 2) *cur_x += 1;
                        break;
                    }
                    case 'L':{
                        if((abs(*cur_y) + abs(*cur_x - 1)) <= 2) *cur_x -= 1;
                        break;
                    }
                }
            }
        }
        if (!strange){
            code[i] = find_keypad_at(*cur_x, *cur_y);
        }else{
            code[i] = find_strange_keypad_at(*cur_x, *cur_y);
        }
        
    }
}

int main(void) {
    Lines l = read_lines("2.txt");

    int cur_x = 1, cur_y = 1;
    char *code = malloc(sizeof(char) * l.count);

    follow_steps(&l, &cur_x, &cur_y, code, false);

    printf("The code is: \n");
    for(size_t i = 0; i < l.count; i++){
        printf("%c", code[i]);
    }

    cur_x = -2;
    cur_y = 0;

    follow_steps(&l, &cur_x, &cur_y, code, true);

    printf("\nThe new code is: \n");
    for(size_t i = 0; i < l.count; i++){
        printf("%c", code[i]);
    }

    free_lines(&l);
    free(code);
    return 0;
}
