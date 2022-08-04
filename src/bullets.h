// 作成者: j19426 西澤駿太郎
#pragma once

#include "bullet.h"

// 弾の最大数
#define BULLETS_MAX 100
// 弾の最大生存時間
#define BULLETS_MAX_AGE 5000

// リングバッファ
typedef struct {
  struct bullet buff[BULLETS_MAX];
  int head;
  int tail;
} bullets_t;

void bulletsInit(bullets_t *bullets);
void bulletsUpdate(bullets_t *bullets, int timeDelta);
void bulletsDraw(const bullets_t *bullets);
