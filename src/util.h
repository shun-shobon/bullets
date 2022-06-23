#pragma once

#include <stdlib.h>

#include "opengl.h"

#define UNUSED __attribute__((unused))

#define INLINE_TEXT(...) #__VA_ARGS__

void *malloc_safe(size_t size);

GLuint create_program(const char *vertex_shader_filepath,
                      const char *fragment_shader_filepath);
