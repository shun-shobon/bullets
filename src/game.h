// 作成者: j19426 西澤駿太郎
#pragma once

#include "bullets.h"
#include "enemies.h"
#include "gamestate.h"
#include "player.h"
#include "shots.h"
#include "spawner.h"

typedef struct {
  gamestate_t gamestate;
  enemies_t enemies;
  player_t player;
  shots_t shots;
  bullets_t bullets;
  spawner_t spawner;
} game_t;

void gameInit(game_t *game);
void gameUpdate(game_t *game);
void gameDraw(const game_t *game);
