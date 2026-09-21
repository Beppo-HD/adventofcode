#include "aoc_str.h"
#include "aoc_io.h"
#include "aoc_vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID 300

typedef struct {
    long chip1, chip2;
    char low_type, high_type;
    int low_id, high_id;
} Bot;

typedef struct {
    int bot_id;
    long value;
} PendingChip;

long part1_answer;

void give_chip(Bot *bots, long *outputs, int bot_id, long value) {
    Bot *b = &bots[bot_id];

    if (b->chip1 == -1) {
        b->chip1 = value;
        return;
    }
    b->chip2 = value;

    long lo = b->chip1 < b->chip2 ? b->chip1 : b->chip2;
    long hi = b->chip1 < b->chip2 ? b->chip2 : b->chip1;

    if (lo == 17 && hi == 61) {
        part1_answer = bot_id;
    }

    if (b->low_type == 'b') give_chip(bots, outputs, b->low_id, lo);
    else outputs[b->low_id] = lo;

    if (b->high_type == 'b') give_chip(bots, outputs, b->high_id, hi);
    else outputs[b->high_id] = hi;

    b->chip1 = -1;
    b->chip2 = -1;
}

int main(void) {
    Lines l = read_lines("input.txt");

    Bot bots[MAX_ID];
    for (int i = 0; i < MAX_ID; i++) {
        bots[i].chip1 = -1;
        bots[i].chip2 = -1;
    }

    long outputs[MAX_ID] = {0};

    Vec pending;
    vec_init(&pending, sizeof(PendingChip));

    for (size_t i = 0; i < l.count; i++) {
        size_t part_count;
        char **parts = str_split(l.lines[i], " ", &part_count);

        if (strcmp(parts[0], "value") == 0) {
            PendingChip pc = { atoi(parts[5]), atol(parts[1]) };
            vec_push(&pending, &pc);
        } else {
            int id = atoi(parts[1]);
            bots[id].low_type = parts[5][0];
            bots[id].low_id = atoi(parts[6]);
            bots[id].high_type = parts[10][0];
            bots[id].high_id = atoi(parts[11]);
        }

        str_split_free(parts, part_count);
    }

    for (size_t i = 0; i < vec_len(&pending); i++) {
        PendingChip *pc = vec_get(&pending, i);
        give_chip(bots, outputs, pc->bot_id, pc->value);
    }
    vec_free(&pending);

    printf("Part 1: %ld\n", part1_answer);
    printf("Part 2: %ld\n", outputs[0] * outputs[1] * outputs[2]);

    free_lines(&l);
    return 0;
}