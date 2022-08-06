// 作成者: j19426 西澤駿太郎
#pragma once

typedef struct {
  int age;
  int score;
  int level;
} gamestate_t;

void gamestateInit(gamestate_t *gamestate);
void gamestateUpdate(gamestate_t *gamestate);
