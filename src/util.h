#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "opengl.h"

void *malloc_safe(size_t size);

uint32_t read_u32_le(const uint8_t *array, size_t offset);

GLuint create_program(const char *vertex_shader_filepath,
                      const char *fragment_shader_filepath);
