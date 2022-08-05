// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "bullets.h"
#include "vector.h"

struct enemy {
  vec2_t position;
  vec2_t velocity;
  float size;
  int age;
  int hp;
  int maxHp;
  void (*move)(struct enemy *self);
  void (*bullet)(struct enemy *self, bullets_t *bullets);
  void (*draw)(struct enemy *self);
  bool shouldRemove;
};
typedef struct enemy enemy_t;

static inline enemy_t enemyNew(vec2_t position, float size, int hp,
                               void (*move)(enemy_t *self),
                               void (*bullet)(enemy_t *self,
                                              bullets_t *bullets),
                               void (*draw)(enemy_t *self)) {
  return (enemy_t){.position = position,
                   .velocity = {0.0F, 0.0F},
                   .size = size,
                   .age = 0,
                   .hp = hp,
                   .maxHp = hp,
                   .move = move,
                   .bullet = bullet,
                   .draw = draw,
                   .shouldRemove = false};
}

void enemyMoveLiner(enemy_t *self);
void enemyBulletNormal(enemy_t *self, bullets_t *bullets);
void enemyDrawSquare(enemy_t *self);
