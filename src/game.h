// 作成者: j19426 西澤駿太郎
#pragma once

#include "bullets.h"
#include "enemies.h"
#include "player.h"
#include "shots.h"
#include "spawner.h"

typedef struct {
  enemies_t enemies;
  player_t player;
  shots_t shots;
  bullets_t bullets;
  spawner_t spawner;
  int age;
} game_state_t;

void gameInit(game_state_t *gameState);
void gameUpdate(game_state_t *gameState);
void gameDraw(const game_state_t *gameState);
