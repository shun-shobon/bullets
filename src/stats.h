// 作成者: j19426 西澤駿太郎
#pragma once

typedef struct {
  int age;
  int score;
  int level;
} stats_t;

void statsInit(stats_t *stats);
void statsUpdate(stats_t *stats);
