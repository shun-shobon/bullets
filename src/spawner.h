// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "enemies.h"
#include "stats.h"

typedef struct {
  int nextSpawnAge;
} spawner_t;

void spawnerInit(spawner_t *spawner, const stats_t *gamestate);
void spawnerUpdate(spawner_t *spawner, enemies_t *enemies,
                   const stats_t *gamestate, bool isGameOver);
