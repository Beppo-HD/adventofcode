/* aoc_io.h — file reading. 
 */
#ifndef AOC_IO_H
#define AOC_IO_H

#include <stddef.h>

typedef struct {
    char **lines;
    size_t count;
} Lines;

/* Reads a file, splits into lines, strips trailing \r\n/whitespace, and
 * skips lines that are blank after stripping. Exits with an error 
 * message if the file can't be opened. */
[[nodiscard]] Lines read_lines(const char *filename);
void  free_lines(Lines *l);

/* Reads the whole file into a single malloc'd, NUL-terminated buffer. 
 * Caller must free() the result. */
[[nodiscard]] char *read_file(const char *filename);

#endif /* AOC_IO_H */
