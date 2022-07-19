#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "opengl.h"

void *mallocSafe(size_t size);

uint32_t readU32Le(const uint8_t *array, size_t offset);

GLuint createProgram(const char *vertex_shader_filepath,
                     const char *fragment_shader_filepath);
