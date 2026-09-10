#include "aoc_str.h"
#include "aoc_io.h"
#include "aoc_grid.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void shift_line(Grid *g, char *dir, size_t line_idx, long amount){
    Grid original = grid_clone(g);
    if(strcmp(dir, "row") == 0){
        for(int i = 0; i < g->cols; i++){
            grid_set(g, line_idx, i, grid_get(&original, line_idx, aoc_mod((i - amount), g->cols)));
        }
    }else{
        for(int i = 0; i < g->rows; i++){
            grid_set(g, i, line_idx, grid_get(&original, aoc_mod((i - amount), g->rows), line_idx));
        }
    }
    grid_free(&original);
}

int main(void) {
    Lines l = read_lines("input.txt");
    Grid screen = grid_create(6, 50, 0);

    for(size_t i = 0; i < l.count; i++){
        size_t part_count;
        char **parts = str_split(l.lines[i], " ", &part_count);

        if(part_count == 2){
            size_t out_count = 0;
            long *dims = str_extract_ints(l.lines[i], &out_count);
            grid_apply_rect(&screen, 0, 0, dims[1] - 1, dims[0] - 1, turn_on);
            free(dims);
        }else{
            char *dir = parts[1];
            size_t out_count = 0;
            long *nums = str_extract_ints(l.lines[i], &out_count);
            shift_line(&screen, dir, nums[0], nums[1]);
        }
        str_split_free(parts, part_count);
    }

    printf("Amount of lights on: %ld\n", grid_sum(&screen));

    for(int j = 0; j < 6; j++){
        for(int i = 0; i < 50; i++){
            if(i % 5 == 0) printf("  ");
            printf("%c", grid_get(&screen, j, i) != 0 ? '#' : '_');
        }
        printf("\n");
    }

    grid_free(&screen);
    free_lines(&l);
    return 0;
}
