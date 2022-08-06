// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "player.h"
#include "vector.h"

#define SHOT_MAX 128

typedef struct {
  vec2_t position;
  vec2_t velocity;
  bool wasHit;
} shot_t;

static inline shot_t shotNew(vec2_t position, vec2_t velocity) {
  return (shot_t){.position = position, .velocity = velocity, false};
}

typedef struct {
  shot_t buff[SHOT_MAX];
  int head;
  int tail;
  int coolTime;
} shots_t;

void shotsInit(shots_t *shots);
void shotsUpdate(shots_t *shots, const player_t *player, bool isGameOver);
void shotsDraw(const shots_t *shots);
