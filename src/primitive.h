// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "texture.h"
#include "vector.h"

void drawCircle(const vec2_t *center, float radius, bool fill);
void drawSquare(const vec2_t *center, float size);
void drawTexture(const vec2_t *center, float size, texture_key_t textureKey);
