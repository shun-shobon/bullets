// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "vector.h"

struct bullet {
  vec2_t position;
  vec2_t vector;
  int age;
  void (*draw)(const struct bullet *self);
};
typedef struct bullet bullet_t;

void bulletDrawDot(const bullet_t *bullet);
