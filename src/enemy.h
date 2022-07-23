// 作成者: j19426 西澤駿太郎
#pragma once

#include "primitive.h"
#include "util.h"

struct enemy {
  vec2_t position;
  int age;
  void (*draw)(struct enemy *self);
  void (*move)(struct enemy *self, int timeDelta);
};
typedef struct enemy enemy_t;

VEC_DECLARE(enemy_t)

void enemiesInit();

void enemiesUpdate(int timeDelta);

void enemiesDraw();
