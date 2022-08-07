// 作成者: j19426 西澤駿太郎
#pragma once

#include "vector.h"

typedef enum {
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT,
} align_t;

void textInit();
float drawText(vec2_t *position, char *str, float height, float alpha,
               align_t align);
