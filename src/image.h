// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdint.h>

#include "opengl.h"
#include "util.h"
#include "err.h"

typedef struct {
  GLuint id;
  uint32_t width;
  uint32_t height;
} texture_t;

void load_bmp(err_t *err, texture_t *texture, char *filepath);
