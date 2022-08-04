// 作成者: j19426 西澤駿太郎
#pragma once

#include "enemies.h"
#include "player.h"
#include "shots.h"

typedef struct {
  enemies_t enemies;
  player_t player;
  shots_t shots;
  int age;
} game_state_t;

void gameInit(game_state_t *gameState);
void gameUpdate(game_state_t *gameState, int timeDelta);
void gameDraw(const game_state_t *gameState);
