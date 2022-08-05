// 作成者: j19426 西澤駿太郎
#pragma once

#include "bullets.h"
#include "vector.h"

typedef struct {
  vec2_t position;
  vec2_t vector;
} player_t;

void playerInit(player_t *player);
void playerUpdate(player_t *player, bullets_t *bullets);
void playerDraw(const player_t *player);
