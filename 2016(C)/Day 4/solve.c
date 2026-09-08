#include "aoc_str.h"
#include "aoc_io.h"
#include "aoc_vec.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char letter;
    size_t count;
} LetterCount;

char *extract_brackets(const char *s) {
    const char *open = strchr(s, '[');
    const char *close = strchr(s, ']');
    if (!open || !close || close <= open) return nullptr;

    size_t len = (size_t)(close - open - 1);
    char *out = malloc(len + 1);
    memcpy(out, open + 1, len);
    out[len] = '\0';
    return out;
}

int compare_by_count_desc(const void *a, const void *b){
    const LetterCount *la = a, *lb = b;
    if(lb->count != la->count) return (int)lb->count - (int)la->count;
    return la->letter - lb->letter;
}

int main(void) {
    Lines l = read_lines("input.txt");
    VecLong valid_room_IDs;
    veclong_init(&valid_room_IDs);
    VecStr valid_room_names;
    vecstr_init(&valid_room_names);

    for(size_t i = 0; i < l.count; i++){
        size_t part_count;
        char **parts = str_split(l.lines[i], "-", &part_count);
        char *checksum = extract_brackets(parts[part_count - 1]);

        StrBuilder room;
        sb_init(&room);
        for(size_t p = 0; p < part_count - 1; p++) sb_append(&room, parts[p]);
        
        LetterCount counts[26];
        for(int j = 0; j < 26; j++){
            counts[j].letter = (char)('a' + j);
            counts[j].count = str_count_char(sb_cstr(&room), (char)('a' + j));
        }

        qsort(counts, 26, sizeof(LetterCount), compare_by_count_desc);

        bool check = true;
        for(int j = 0; j < 5; j++) if(counts[j].letter != checksum[j]) check = false;
        if(check){
            int ID = atoi(parts[part_count - 1]);
            veclong_push(&valid_room_IDs, ID);
            vecstr_push(&valid_room_names, str_rotate(sb_cstr(&room), ID));
        }
        free(checksum);
        sb_free(&room);
        str_split_free(parts, part_count);
    }

    long sector_sum = 0;
    for(size_t i = 0; i < veclong_len(&valid_room_IDs); i++) sector_sum += veclong_get(&valid_room_IDs, i);
    
    printf("The sum of the sector IDs is: %ld\n", sector_sum);

    for(size_t i = 0; i < vecstr_len(&valid_room_names); i++){
        if(str_contains(vecstr_get(&valid_room_names, i), "northpoleobjectstorage")){
            printf("Room ID of North Pole objects storage: %ld", veclong_get(&valid_room_IDs, i));
        }
    }

    vecstr_free(&valid_room_names);
    veclong_free(&valid_room_IDs);
    free_lines(&l);
    return 0;
}
