// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdint.h>

#include "opengl.h"
#include "util.h"

typedef struct {
  GLuint id;
  uint32_t width;
  uint32_t height;
} texture_t;

err_t load_bmp(char *filepath, texture_t *texture);
