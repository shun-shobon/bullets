// 作成者: j19426 西澤駿太郎
#pragma once

#include "opengl.h"

typedef enum {
  TEXTURE_PLAYER,
  TEXTURE_ENEMY_A,
  TEXTURE_ENEMY_B,
  TEXTURE_SHOT,
  TEXTURE_BULLET_A,
  TEXTURE_BULLET_B,
  TEXTURE_TITLE,
  TEXTURE_GAMEOVER,
  TEXTURE_LENGTH,
} texture_key_t;

typedef struct {
  GLuint id;
  pngInfo info;
} texture_t;

extern texture_t textures[TEXTURE_LENGTH];

void textureInit();
