// 作成者: j19426 西澤駿太郎
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opengl.h"

int globalTimeDelta = 0;
int globalFps = 0;

void deltaTimeUpdate() {
  static int timeBefore = 0;
  static int timeBeforeCalcFps = 0;
  static int frameCount = 0;

  int timeNow = glutGet(GLUT_ELAPSED_TIME);
  globalTimeDelta = timeNow - timeBefore;
  timeBefore = timeNow;

  frameCount++;
  if (1000 < timeNow - timeBeforeCalcFps) {
    globalFps = frameCount;
    timeBeforeCalcFps = timeNow;
    frameCount = 0;
  }
}

void fpsDraw() {
  char fpsStr[8];
  snprintf(fpsStr, 8, "%02d fps", globalFps);
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

void *malloc_safe(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    abort();
  }

  return ptr;
}

void *realloc_safe(void *ptr, size_t size) {
  void *newPtr = realloc(ptr, size);
  if (newPtr == NULL) {
    free(ptr);
    abort();
  }

  return newPtr;
}
