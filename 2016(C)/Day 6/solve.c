#include "aoc_str.h"
#include "aoc_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char letter;
    size_t count;
} LetterCount;

int main(void) {
    Lines l = read_lines("input.txt");
    size_t message_length = strlen(l.lines[0]);
    char *message = malloc(sizeof(char) * message_length + 1);
    char *modified_message = malloc(sizeof(char) * message_length + 1);
    for(size_t i = 0; i < message_length; i++){
        LetterCount counts[26] = {0};
        for(size_t j = 0; j < l.count; j++){
            char c = l.lines[j][i];
            counts[c - 'a'].letter = c;
            counts[c - 'a'].count += 1;
        }

        size_t maxCount = counts[0].count;
        int maxIndex = 0;
        size_t minCount = counts[0].count;
        int minIndex = 0;
        for (int j = 1; j < 26; j++) {
            if (counts[j].count > maxCount) {
                maxCount = counts[j].count;
                maxIndex = j;
            }
            if (counts[j].count < minCount) {
                minCount = counts[j].count;
                minIndex = j;
            }
        }

        message[i] = counts[maxIndex].letter;
        modified_message[i] = counts[minIndex].letter;
    }
    message[message_length] = '\0';
    modified_message[message_length] = '\0';

    printf("The message from highest char counts is: %s\n", message);
    printf("The message from lowest char counts is: %s", modified_message);

    free_lines(&l);
    return 0;
}
