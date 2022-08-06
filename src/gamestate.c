// 作成者: j19426 西澤駿太郎
#include "gamestate.h"

#include <math.h>

void gamestateInit(gamestate_t *gamestate) {
  gamestate->age = 0;
  gamestate->score = 0;
  gamestate->level = 0;
}

void gamestateUpdate(gamestate_t *gamestate) {
  gamestate->age += 1;
  gamestate->level = (int)sqrtf((float)(gamestate->score) / 100.0F);
}
