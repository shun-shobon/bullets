// 作成者: j19426 西澤駿太郎
#pragma once

#include "enemy.h"
#include "player.h"

typedef struct {
  enemies_t enemies;
  player_t player;
  int age;
} game_state_t;

void gameDraw(game_state_t *gameState);

void gameInit(game_state_t *gameState);

void gameUpdate(game_state_t *gameState, int timeDelta);
