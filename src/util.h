// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdlib.h>

extern int globalTimeDelta;
extern int globalFps;

void deltaTimeUpdate();
void fpsDraw();

void *malloc_safe(size_t size);
void *realloc_safe(void *ptr, size_t size);

// 可変長配列の宣言
#define VEC_DECLARE(T)                     \
  typedef struct {                         \
    size_t cap;                            \
    size_t len;                            \
    T *ptr;                                \
  } vec_##T;                               \
  void vec_init_##T(vec_##T *vec);         \
  void vec_push_##T(vec_##T *vec, T item); \
  void vec_free_##T(vec_##T *vec);

// 可変長配列の実装
#define VEC_IMPL(T)                                            \
  void vec_init_##T(vec_##T *vec) {                            \
    vec->cap = 1;                                              \
    vec->len = 0;                                              \
    vec->ptr = NULL;                                           \
  }                                                            \
  void vec_push_##T(vec_##T *vec, T item) {                    \
    vec->len += 1;                                             \
    if (vec->cap <= vec->len) {                                \
      vec->cap *= 2;                                           \
      vec->ptr = realloc_safe(vec->ptr, sizeof(T) * vec->cap); \
    }                                                          \
    vec->ptr[vec->len - 1] = item;                             \
  }                                                            \
  void vec_free_##T(vec_##T *vec) { free(vec->ptr); }
