// 作成者: j19426 西澤駿太郎
#include "util.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void *mallocSafe(size_t size) {
  void *ptr = malloc(size);
  if (!ptr) {
    abort();
  }

  return ptr;
}

float absf(float x) { return x < 0.0F ? -x : x; }
float randf() { return (float)rand() / (float)RAND_MAX; }
float expRandf(float lambda) { return -1.0F / lambda * logf(randf()); }
float expRandNormalizedf(float lambda) {
  while (true) {
    float val = expRandf(lambda);
    if (val <= 1.0F) return val;
  }
}
