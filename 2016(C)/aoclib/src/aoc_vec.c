#include "aoc_vec.h"
#include "aoc_str.h"
#include <stdlib.h>
#include <string.h>

void vec_init(Vec *v, size_t elem_size) {
    v->data = nullptr;
    v->elem_size = elem_size;
    v->len = 0;
    v->cap = 0;
}

void vec_free(Vec *v) {
    free(v->data);
    v->data = nullptr;
    v->len = v->cap = 0;
}

void vec_reserve(Vec *v, size_t min_cap) {
    if (v->cap >= min_cap) return;
    size_t new_cap = v->cap ? v->cap * 2 : 8;
    if (new_cap < min_cap) new_cap = min_cap;
    v->data = realloc(v->data, new_cap * v->elem_size);
    v->cap = new_cap;
}

void vec_push(Vec *v, const void *elem) {
    vec_reserve(v, v->len + 1);
    memcpy((char *)v->data + v->len * v->elem_size, elem, v->elem_size);
    v->len++;
}

void vec_pop(Vec *v) {
    if (v->len > 0) v->len--;
}

void *vec_get(const Vec *v, size_t idx) {
    if (idx >= v->len) return nullptr;
    return (char *)v->data + idx * v->elem_size;
}

void vec_set(Vec *v, size_t idx, const void *elem) {
    if (idx >= v->len) return;
    memcpy((char *)v->data + idx * v->elem_size, elem, v->elem_size);
}

void vec_clear(Vec *v) {
    v->len = 0;
}

size_t vec_len(const Vec *v) {
    return v->len;
}

/* ---- typed wrappers ---- */

void veclong_init(VecLong *v) { vec_init(&v->v, sizeof(long)); }
void veclong_push(VecLong *v, long x) { vec_push(&v->v, &x); }
long veclong_get(const VecLong *v, size_t idx) {
    long *p = vec_get(&v->v, idx);
    return p ? *p : 0;
}
void veclong_free(VecLong *v) { vec_free(&v->v); }
size_t veclong_len(const VecLong *v) { return vec_len(&v->v); }

void vecstr_init(VecStr *v) { vec_init(&v->v, sizeof(char *)); }
void vecstr_push(VecStr *v, const char *s) {
    char *copy = aoc_strdup(s);
    vec_push(&v->v, &copy);
}
const char *vecstr_get(const VecStr *v, size_t idx) {
    char **p = vec_get(&v->v, idx);
    return p ? *p : nullptr;
}
void vecstr_free(VecStr *v) {
    for (size_t i = 0; i < v->v.len; i++) {
        char **p = vec_get(&v->v, i);
        free(*p);
    }
    vec_free(&v->v);
}
size_t vecstr_len(const VecStr *v) { return vec_len(&v->v); }
