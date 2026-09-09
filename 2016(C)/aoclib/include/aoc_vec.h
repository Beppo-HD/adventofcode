/* aoc_vec.h — growable arrays.
 */
#ifndef AOC_VEC_H
#define AOC_VEC_H

#include <stddef.h>

typedef struct {
    void   *data;
    size_t  elem_size;
    size_t  len;
    size_t  cap;
} Vec;

void   vec_init(Vec *v, size_t elem_size);
void   vec_free(Vec *v);
void   vec_reserve(Vec *v, size_t min_cap);
void   vec_push(Vec *v, const void *elem);
void   vec_pop(Vec *v); /* removes last element, no-op if empty */
void  *vec_get(const Vec *v, size_t idx); /* nullptr if out of range */
void   vec_set(Vec *v, size_t idx, const void *elem);
void   vec_clear(Vec *v); /* keeps capacity */
size_t vec_len(const Vec *v);

typedef struct { Vec v; } VecLong;   /* array of long   */
typedef struct { Vec v; } VecStr;    /* array of char*  */

void   veclong_init(VecLong *v);
void   veclong_push(VecLong *v, long x);
long   veclong_get(const VecLong *v, size_t idx);
void   veclong_free(VecLong *v);
size_t veclong_len(const VecLong *v);

void   vecstr_init(VecStr *v);
void   vecstr_push(VecStr *v, const char *s); /* copies s */
const char *vecstr_get(const VecStr *v, size_t idx);
void   vecstr_free(VecStr *v); /* frees all owned strings too */
size_t vecstr_len(const VecStr *v);

#endif /* AOC_VEC_H */
