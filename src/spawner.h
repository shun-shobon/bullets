// 作成者: j19426 西澤駿太郎
#pragma once

#include "enemies.h"

typedef struct {
  int nextSpawnAge;
} spawner_t;

void spawnerInit(spawner_t *spawner);
void spawnerUpdate(spawner_t *spawner, enemies_t *enemies, int age);
