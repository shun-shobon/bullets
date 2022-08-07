// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "consts.h"
#include "game.h"
#include "title.h"

typedef struct {
  phase_t phase;
  title_t title;
  game_t game;
  phase_t moveNextPhase;
  bool isPause;
} global_t;

void globalInit(global_t *global);
void globalUpdate(global_t *global);
void globalDraw(const global_t *global);
