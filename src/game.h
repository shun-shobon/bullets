// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "bullets.h"
#include "consts.h"
#include "enemies.h"
#include "player.h"
#include "shots.h"
#include "spawner.h"
#include "stats.h"

typedef struct {
  bool isGameOver;
  stats_t stats;
  enemies_t enemies;
  player_t player;
  shots_t shots;
  bullets_t bullets;
  spawner_t spawner;
} game_t;

void gameInit(game_t *game);
void gameDrop(game_t *game);
void gameUpdate(game_t *game, phase_t *moveNextPhase);
void gameDraw(const game_t *game);
