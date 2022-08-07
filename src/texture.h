// 作成者: j19426 西澤駿太郎
#pragma once

#include "opengl.h"
#include "vector.h"

typedef enum {
  TEXTURE_PLAYER,
  TEXTURE_ENEMY_A,
  TEXTURE_ENEMY_B,
  TEXTURE_SHOT,
  TEXTURE_BULLET_A,
  TEXTURE_BULLET_B,
  TEXTURE_TITLE,
  TEXTURE_GAMEOVER,
  TEXTURE_CURSOR,
  TEXTURE_LENGTH,
} texture_key_t;

typedef struct {
  GLuint id;
  pngInfo info;
} texture_t;

void textureInit();
void drawTexture(const vec2_t *center, float size, float alpha,
                 texture_key_t textureKey);
