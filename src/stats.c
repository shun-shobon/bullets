// 作成者: j19426 西澤駿太郎
#include "stats.h"

#include <math.h>

void statsInit(stats_t *stats) {
  stats->age = 0;
  stats->score = 0;
  stats->level = 0;
}

void statsUpdate(stats_t *stats) {
  stats->age += 1;
  stats->level = (int)sqrtf((float)(stats->score) / 100.0F);
}
