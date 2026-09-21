#include "aoc_str.h"
#include "aoc_io.h"
#include "aoc_vec.h"
#include "aoc_set.h"
#include "aoc_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITEMS 16
#define TOP_FLOOR 4

typedef struct {
    int elevator;           // The floor the elevator is currently on
    int floor[MAX_ITEMS];   // The floor an Item is currently on
    char type[MAX_ITEMS];   // 'g' = generator, 'm' = microchip
    int element[MAX_ITEMS]; // matching id for a generator+chip pair of the same element
    int item_count;
} State;

bool is_valid(State *s) {
    for (int i = 0; i < s->item_count; i++){
        if (s->type[i] == 'g') continue;
        int cur_id = s->element[i];
        int cur_floor = s->floor[i];
        bool has_gen = false, diff_gen = false;
        for (int j = 0; j < s->item_count; j++){
            if (s->type[j] == 'm' || s->floor[j] != cur_floor) continue;
            if (cur_id == s->element[j]){
                has_gen = true;
            } else {
                diff_gen = true;
            }
        }
        if (diff_gen && !has_gen) return false;
    }
    return true;
}

bool is_goal(State *s) {
    for (int i = 0; i < s->item_count; i++){
        if (s->floor[i] != TOP_FLOOR) return false;
    }
    return true;
}

int compare_pairs(const void *a, const void *b) {
    const int *pa = a;
    const int *pb = b;
    if (pa[0] != pb[0]) return pa[0] - pb[0];
    return pa[1] - pb[1];
}

char *serialize_state(State *s) {
    int gen_floor[MAX_ITEMS];
    int chip_floor[MAX_ITEMS];
    for (int i = 0; i < MAX_ITEMS; i++) {
        gen_floor[i] = -1;
        chip_floor[i] = -1;
    }

    int max_element = -1;
    for (int i = 0; i < s->item_count; i++) {
        int e = s->element[i];
        if (e > max_element) max_element = e;
        if (s->type[i] == 'g') gen_floor[e] = s->floor[i];
        else chip_floor[e] = s->floor[i];
    }

    int pair_count = max_element + 1;
    int pairs[MAX_ITEMS][2];
    for (int e = 0; e < pair_count; e++) {
        pairs[e][0] = gen_floor[e];
        pairs[e][1] = chip_floor[e];
    }

    qsort(pairs, pair_count, sizeof(pairs[0]), compare_pairs);

    StrBuilder state;
    sb_init(&state);

    sb_append(&state, "E:");
    char *elevator_str = to_string(s->elevator);
    sb_append(&state, elevator_str);
    free(elevator_str);

    sb_append(&state, ",P:[");
    for (int e = 0; e < pair_count; e++) {
        sb_append(&state, "(");

        char *g = to_string(pairs[e][0]);
        sb_append(&state, g);
        free(g);

        sb_append(&state, ",");

        char *c = to_string(pairs[e][1]);
        sb_append(&state, c);
        free(c);

        sb_append(&state, ")");
    }
    sb_append(&state, "]");

    char *out = aoc_strdup(sb_cstr(&state));
    sb_free(&state);
    return out;
}


int find_items_on_floor(State *cur, int floor, int *out_indices) {
    int count = 0;
    for (int i = 0; i < cur->item_count; i++){
        if (cur->floor[i] != floor) continue;
        out_indices[count] = i;
        count++;
    }
    return count;
}

State apply_move(State *cur, int idx1, int idx2, int new_floor) {
    State new_state = *cur;
    new_state.elevator = new_floor;
    new_state.floor[idx1] = new_floor;
    if (idx2 != -1){
        new_state.floor[idx2] = new_floor;
    }
    return new_state;
}

void generate_moves(State *cur, Vec *next, StrSet *visited) {
    int items[MAX_ITEMS];
    int count = find_items_on_floor(cur, cur->elevator, items);

    for (int direction = -1; direction <= 1; direction += 2) {
        int new_floor = cur->elevator + direction;
        if (new_floor < 1 || new_floor > TOP_FLOOR) continue;

        for (int i = 0; i < count; i++) {
            State moved = apply_move(cur, items[i], -1, new_floor);
            if (!is_valid(&moved)) continue;
            char *key = serialize_state(&moved);
            if (strset_contains(visited, key)) { 
                free(key); 
                continue; 
            }
            strset_add(visited, key);
            free(key);
            vec_push(next, &moved);
        }

        for (int i = 0; i < count; i++){
            for (int j = i + 1; j < count; j++) { 
                State moved = apply_move(cur, items[i], items[j], new_floor);
                if (!is_valid(&moved)) continue;
                char *key = serialize_state(&moved);
                if (strset_contains(visited, key)) { 
                    free(key); 
                    continue; 
                }
                strset_add(visited, key);
                free(key);
                vec_push(next, &moved);
            }
        }
    }
}

int bfs(State state) {
    if (is_goal(&state)) return 0;
    StrSet visited;
    strset_init(&visited);
    Vec prev;
    vec_init(&prev, sizeof(State));
    Vec next;
    vec_init(&next, sizeof(State));
    generate_moves(&state, &next, &visited);
    for(int step = 1; ; step++){
        for(size_t i = 0; i < vec_len(&next); i++){
            if(is_goal(vec_get(&next, i))){
                return step;
            }
            vec_push(&prev, vec_get(&next, i));
        }
        vec_clear(&next);
        for(size_t i = 0; i < vec_len(&prev); i++){
            generate_moves(vec_get(&prev, i), &next, &visited);
        }
        vec_clear(&prev);
    }    
}


int main(void) {
    Lines l = read_lines("input.txt");
    State start = { .elevator = 1, .item_count = 0 };

    Map element_ids;
    map_init(&element_ids);
    
    for(size_t i = 0; i < l.count; i++){
        VecStr computer_parts;
        vecstr_init(&computer_parts);
        size_t out_count;
        char **parts = str_split(l.lines[i], " ", &out_count);

        for(size_t j = 0; j < out_count; j++){
            if(str_starts_with(parts[j], "generator") || str_starts_with(parts[j], "microchip")){
                vecstr_push(&computer_parts, parts[j - 1]);
            }else{
                continue;
            }
        }

        for(size_t j = 0; j < vecstr_len(&computer_parts); j++){
            const char *part = vecstr_get(&computer_parts, j);
            size_t count;
            char *element = str_split(part, "-", &count)[0];

            long id;
            if(!map_get(&element_ids, element, &id)){
                id = (long)map_count(&element_ids);
                map_set(&element_ids, element, id);
            }

            start.floor[start.item_count] = (int)i + 1;
            start.element[start.item_count] = (int)id;
            start.type[start.item_count] = (count == 1) ? 'g' : 'm';
            start.item_count++;
        }
        vecstr_free(&computer_parts);
    }
    
    printf("Minimal moves to solve Part 1: %d\n", bfs(start));

    size_t next_id = map_count(&element_ids);
    int count = start.item_count;
    for(int i = 0; i < 4; i++){
        start.element[count + i] = next_id + (i/2);
        start.floor[count + i] = 1;
        start.type[count + i] = i % 2 == 0 ? 'g' : 'm';
    }
    start.item_count += 4;

    printf("Minimal moves to solve Part 2: %d\n", bfs(start));

    free_lines(&l);
    map_free(&element_ids);
    return 0;
}