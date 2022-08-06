// 作成者: j19426 西澤駿太郎
#include "util.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opengl.h"

void fpsInit(fps_t *fps) {
  for (int i = 0; i < FPS_BUFF_MAX; i++) {
    fps->buff[i] = 0;
  }
  fps->head = 0;
  fps->sum = 0;
  fps->before = 0;
  fps->init = 0;
  fps->fps = 0;
}

void fpsUpdate(fps_t *fps) {
  int now = glutGet(GLUT_ELAPSED_TIME);
  int delta = now - fps->before;
  fps->before = now;

  if (fps->init < FPS_BUFF_MAX) {
    fps->buff[fps->init] = delta;
    fps->init += 1;

    if (FPS_BUFF_MAX <= fps->init) {
      for (int i = 0; i < FPS_BUFF_MAX; i++) {
        fps->sum += fps->buff[i];
      }
    }

    return;
  }

  fps->sum -= fps->buff[fps->head];
  fps->sum += delta;
  fps->buff[fps->head] = delta;
  fps->head += 1;
  if (FPS_BUFF_MAX <= fps->head) {
    fps->head = 0;
  }

  fps->fps = 1000 * FPS_BUFF_MAX / fps->sum;
}

void fpsDraw(const fps_t *fps) {
  char fpsStr[8];
  snprintf(fpsStr, 8, "%02d fps", fps->fps);
  unsigned int length = strlen(fpsStr);

  glColor3ub(0x00, 0x00, 0x00);
  glRasterPos2f(6.0F, 5.0F);
  for (unsigned int i = 0; i < length; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, fpsStr[i]);
  }

  glColor3ub(0xff, 0xff, 0xff);
  glRasterPos2f(5.0F, 6.0F);
  for (unsigned int i = 0; i < length; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, fpsStr[i]);
  }
}

void *mallocSafe(size_t size) {
  void *ptr = malloc(size);
  if (!ptr) {
    abort();
  }

  return ptr;
}

float clampf(float min, float max, float x) {
  if (x < min) return min;
  if (max < x) return max;
  return x;
}
float absf(float x) { return x < 0.0F ? -x : x; }
float randomf() { return (float)random() / (float)RAND_MAX; }
float expRandomf(float lambda) { return -1.0F / lambda * logf(randomf()); }
float expRandomNormalizedf(float lambda) {
  while (true) {
    float val = expRandomf(lambda);
    if (val <= 1.0F) return val;
  }
}
