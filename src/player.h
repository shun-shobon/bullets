// 作成者: j19426 西澤駿太郎
#pragma once

#include "primitive.h"

typedef struct {
  vec2 position;
  vec2 vector;
} player_t;

void player_update(int time_delta);

void player_draw();
