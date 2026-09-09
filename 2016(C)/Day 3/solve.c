#include "aoclib.h"
#include <stdio.h>
#include <stdlib.h>

int check_triangle(int *n){
    return (n[0] + n[1] > n[2] && n[0] + n[2] > n[1] && n[1] + n[2] > n[0]) ? 1 : 0;
}

int check_list(int *n, size_t len){
    int valid_counter = 0;
    for(size_t i = 0; i + 2 < len; i += 3){
        valid_counter += check_triangle(&n[i]);
    }
    return valid_counter;
}

int main(void) {
    Lines l = read_lines("input.txt");

    int *all_numbers = malloc(sizeof(int) * l.count * 3);
    for(size_t i = 0; i < l.count; i++){
        size_t num_count;
        long *nums = str_extract_ints(l.lines[i], &num_count);
        for(size_t j = 0; j < num_count; j++){
            all_numbers[i * 3 + j] = nums[j];
        }
        free(nums);
    }

    printf("There are %d valid triangles.", check_list(all_numbers, l.count * 3));

    int *new_all_numbers = malloc(sizeof(int) * l.count * 3);

    size_t out = 0;
    for (size_t block = 0; block * 9 < l.count*3; block++) {
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                size_t idx = block * 9 + row * 3 + col;
                if (idx >= l.count*3) break;
                new_all_numbers[out++] = all_numbers[idx];
            }
        }
    }

    printf("\nWith the new rules there are %d valid triangles.", check_list(new_all_numbers, l.count * 3));

    free_lines(&l);
    return 0;
}
