// 作成者: j19426 西澤駿太郎
#include "texture.h"

#include <stdio.h>

#include "opengl.h"

texture_t textures[TEXTURE_LENGTH];

void textureInit() {
  char pathStr[32];

  for (int i = 0; i < TEXTURE_LENGTH; i++) {
    snprintf(pathStr, 32, "./assets/img%d.png", i);
    textures[i].id =
        pngBind(pathStr, PNG_NOMIPMAP, PNG_ALPHA, &textures[i].info, GL_CLAMP,
                GL_NEAREST, GL_NEAREST);
  }
}
