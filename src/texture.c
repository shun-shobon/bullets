// 作成者: j19426 西澤駿太郎
#include "texture.h"

#include <stdio.h>

#include "opengl.h"

static texture_t textures[TEXTURE_LENGTH];

void textureInit() {
  char pathStr[32];

  for (int i = 0; i < TEXTURE_LENGTH; i++) {
    snprintf(pathStr, 32, "./assets/img%d.png", i);
    textures[i].id =
        pngBind(pathStr, PNG_NOMIPMAP, PNG_ALPHA, &textures[i].info, GL_CLAMP,
                GL_NEAREST, GL_NEAREST);
  }
}

void drawTexture(const vec2_t *center, float size, float alpha,
                 texture_key_t textureKey) {
  texture_t *texture = &textures[textureKey];

  glPushMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  glColor4f(1.0F, 1.0F, 1.0F, alpha);

  glBegin(GL_QUADS);

  glTexCoord2f(0.0F, 1.0F);
  glVertex2f(center->x - size / 2.0F, center->y - size / 2.0F);

  glTexCoord2f(1.0F, 1.0F);
  glVertex2f(center->x + size / 2.0F, center->y - size / 2.0F);

  glTexCoord2f(1.0F, 0.0F);
  glVertex2f(center->x + size / 2.0F, center->y + size / 2.0F);

  glTexCoord2f(0.0F, 0.0F);
  glVertex2f(center->x - size / 2.0F, center->y + size / 2.0F);

  glEnd();

  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}
