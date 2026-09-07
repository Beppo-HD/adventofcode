
#include "aoc_math.h"
#include "aoc_str.h"
#include "aoc_io.h"
#include "aoc_set.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Lines l = read_lines("1.txt");
    size_t part_count;
    char **parts = str_split(l.lines[0], ", ", &part_count);

    long cur_x = 0, cur_y = 0;
    bool found = false;
    long twice_visited_x = 0, twice_visited_y = 0;
    char facing = 0; // 0:north, 1:east 2:south 3:west
    PairSet ps;
    pairset_init(&ps);

    for(size_t i = 0; i < part_count; i++){
        char turn = str_starts_with(parts[i], "R") ? 'R' : 'L';
        facing = aoc_mod((turn == 'R' ? facing + 1 : facing - 1), 4);
        size_t n;
        long *nums = str_extract_ints(parts[i], &n);
        long distance = nums[0];
        free(nums); 
       
        for(long j = 0; j < distance; j++){
            cur_x = facing == 1 ? cur_x + 1 : facing == 3 ? cur_x - 1 : cur_x;
            cur_y = facing == 0 ? cur_y + 1 : facing == 2 ? cur_y - 1 : cur_y;
            size_t cur_count = pairset_count(&ps);
            pairset_add(&ps, cur_x, cur_y);
            if(cur_count == pairset_count(&ps)){
                if(!found){
                    found = true;
                    twice_visited_x = cur_x;
                    twice_visited_y = cur_y;
                }
            }
        }
    }

    printf("He is %ld blocks away\n", labs(cur_x) + labs(cur_y));
    printf("The first position he revisits is (%ld, %ld) which is %ld blocks away", twice_visited_x, twice_visited_y, labs(twice_visited_x) + labs(twice_visited_y));

    pairset_free(&ps);
    str_split_free(parts, part_count);
    free_lines(&l);
    return 0;
}
