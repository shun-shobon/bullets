#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "opengl.h"

typedef enum {
  ERR_NO,         // エラーが生じていない
  ERR_FILE_LOAD,  // ファイル読み込みエラー
} err_t;

void *malloc_safe(size_t size);

uint32_t read_u32_le(const uint8_t *array, size_t offset);

GLuint create_program(const char *vertex_shader_filepath,
                      const char *fragment_shader_filepath);
