// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdlib.h>

#define FPS_BUFF_MAX 10
typedef struct {
  int buff[FPS_BUFF_MAX];
  int head;
  int sum;
  int before;
  int init;
  int fps;
} fps_t;

void fpsInit(fps_t *fps);
void fpsUpdate(fps_t *fps);
void fpsDraw(const fps_t *fps);

void *mallocSafe(size_t size);

float clampf(float min, float max, float x);
float absf(float x);
float randomf();
float expRandomf(float lambda);
float expRandomNormalizedf(float lambda);
