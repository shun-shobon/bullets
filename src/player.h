// 作成者: j19426 西澤駿太郎
#pragma once

#include "primitive.h"

typedef struct {
  vec2_t position;
  vec2_t vector;
} player_t;

void playerInit(player_t *player);
void playerUpdate(player_t *player, int timeDelta);
void playerDraw(player_t *player);
