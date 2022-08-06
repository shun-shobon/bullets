// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "vector.h"

struct bullet {
  vec2_t position;
  vec2_t velocity;
  float size;
  int age;
  bool wasHit;
  void (*draw)(const struct bullet *self);
};
typedef struct bullet bullet_t;

static inline bullet_t bulletNew(vec2_t position, vec2_t velocity, float size,
                                 void (*draw)(const bullet_t *self)) {
  return (bullet_t){.position = position,
                    .velocity = velocity,
                    .size = size,
                    .age = 0,
                    .wasHit = false,
                    .draw = draw};
}

void bulletDrawA(const bullet_t *bullet);
void bulletDrawB(const bullet_t *bullet);
