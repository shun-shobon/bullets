// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "vector.h"

struct enemy {
  vec2_t position;
  int age;
  void (*draw)(struct enemy *self);
  void (*move)(struct enemy *self);
  bool shouldRemove;
};
typedef struct enemy enemy_t;

void enemyMoveLiner(enemy_t *self);
void enemyDrawSquare(enemy_t *self);
