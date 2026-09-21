/* aoc_grid.h — 2D grid of ints.
 */
#ifndef AOC_GRID_H
#define AOC_GRID_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *cells;   /* row-major, rows*cols ints */
    int  rows;
    int  cols;
} Grid;

/* Pre-made actions for convenience */
static inline int turn_on(int cell_value) {
    return cell_value == 0 ? 1 : cell_value;
}

static inline int turn_off(void) {
    return 0;
}

static inline int toggle(int cell_value) {
    return cell_value ? 0 : 1;
}

static inline int increase(int cell_value) {
    return cell_value + 1;
}

static inline int decrease(int cell_value) {
    return cell_value - 1;
}

[[nodiscard]] Grid grid_create(int rows, int cols, int init_val);
void grid_free(Grid *g);
[[nodiscard]] Grid grid_clone(const Grid *g);

static inline int grid_get(const Grid *g, int r, int c) {
    return g->cells[r * g->cols + c];
}
static inline void grid_set(Grid *g, int r, int c, int v) {
    g->cells[r * g->cols + c] = v;
}

/* Apply `action` to every cell with row in [r1, r2] and col in [c1, c2] inclusive */
void grid_apply_rect(Grid *g, int r1, int c1, int r2, int c2, int (*action)(int));

/* Sum of all cell values. */
long grid_sum(const Grid *g);

#endif /* AOC_GRID_H */
