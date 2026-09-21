#include "aoc_grid.h"
#include <stdlib.h>
#include <string.h>

Grid grid_create(int rows, int cols, int init_val) {
    Grid g;
    g.rows = rows;
    g.cols = cols;
    g.cells = malloc((size_t)rows * (size_t)cols * sizeof(int));
    for (long i = 0; i < (long)rows * cols; i++) g.cells[i] = init_val;
    return g;
}

void grid_free(Grid *g) {
    free(g->cells);
    g->cells = nullptr;
    g->rows = g->cols = 0;
}

Grid grid_clone(const Grid *g) {
    Grid out;
    out.rows = g->rows;
    out.cols = g->cols;
    size_t n = (size_t)g->rows * (size_t)g->cols;
    out.cells = malloc(n * sizeof(int));
    memcpy(out.cells, g->cells, n * sizeof(int));
    return out;
}

void grid_apply_rect(Grid *g, int r1, int c1, int r2, int c2, int (*action)(int)) {
    for (int r = r1; r <= r2; r++)
        for (int c = c1; c <= c2; c++)
            grid_set(g, r, c, action(grid_get(g, r, c)));
}

long grid_sum(const Grid *g) {
    long total = 0;
    for (long i = 0; i < (long)g->rows * g->cols; i++) total += g->cells[i];
    return total;
}
