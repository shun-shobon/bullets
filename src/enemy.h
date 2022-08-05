// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "bullets.h"
#include "vector.h"

struct enemy {
  vec2_t position;
  vec2_t vector;
  float size;
  int age;
  void (*move)(struct enemy *self);
  void (*bullet)(struct enemy *self, bullets_t *bullets);
  void (*draw)(struct enemy *self);
  bool shouldRemove;
};
typedef struct enemy enemy_t;

void enemyMoveLiner(enemy_t *self);
void enemyBulletNormal(enemy_t *self, bullets_t *bullets);
void enemyDrawSquare(enemy_t *self);
