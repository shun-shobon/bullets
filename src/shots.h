// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "player.h"
#include "vector.h"

#define SHOT_MAX 30

typedef struct {
  vec2_t position;
  vec2_t vector;
  bool didHit;
} shot_t;

typedef struct {
  shot_t buff[SHOT_MAX];
  int head;
  int tail;
} shots_t;

void shotsInit(shots_t *shots);
void shotsUpdate(shots_t *shots, int timeDelta, const player_t *player);
void shotsDraw(const shots_t *shots);
