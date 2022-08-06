// 作成者: j19426 西澤駿太郎
#include "text.h"

#include <stdio.h>
#include <string.h>

#include "opengl.h"
#include "texture.h"
#include "vector.h"

static void drawChar(vec2_t *position, char c, float height, float alpha);

static texture_t alphabetTextures['Z' - 'A' + 1];
static texture_t numberTextures['9' - '0' + 1];
static texture_t spaceTexture;

void textInit() {
  char pathStr[32];

  for (int i = 0; i < 'Z' - 'A' + 1; i++) {
    snprintf(pathStr, 32, "./assets/text%c.png", 'A' + i);
    alphabetTextures[i].id =
        pngBind(pathStr, PNG_NOMIPMAP, PNG_ALPHA, &alphabetTextures[i].info,
                GL_CLAMP, GL_NEAREST, GL_NEAREST);
  }

  for (int i = 0; i < '9' - '0' + 1; i++) {
    snprintf(pathStr, 32, "./assets/text%c.png", '0' + i);
    numberTextures[i].id =
        pngBind(pathStr, PNG_NOMIPMAP, PNG_ALPHA, &numberTextures[i].info,
                GL_CLAMP, GL_NEAREST, GL_NEAREST);
  }

  snprintf(pathStr, 32, "./assets/text .png");
  spaceTexture.id =
      pngBind(pathStr, PNG_NOMIPMAP, PNG_ALPHA, &spaceTexture.info, GL_CLAMP,
              GL_NEAREST, GL_NEAREST);
}

void drawText(vec2_t *position, char *str, float height, float alpha,
              align_t align) {
  int length = (int)strlen(str);
  float width = (float)length * height;

  vec2_t charPosition;
  charPosition.y = position->y;
  switch (align) {
    case ALIGN_LEFT:
      charPosition.x = position->x + height / 2.0F;
      break;
    case ALIGN_CENTER:
      charPosition.x = position->x - width / 2.0F + height / 2.0F;
      break;
    case ALIGN_RIGHT:
      charPosition.x = position->x + width / 2.0F - height / 2.0F;
      break;
  }

  for (int i = 0; i < length; i++) {
    drawChar(&charPosition, str[i], height, alpha);
    charPosition.x += height;
  }
}

static void drawChar(vec2_t *position, char c, float height, float alpha) {
  texture_t *texture;
  if ('0' <= c && c <= '9') {
    texture = &numberTextures[c - '0'];
  } else if ('A' <= c && c <= 'Z') {
    texture = &alphabetTextures[c - 'A'];
  } else {
    texture = &spaceTexture;
  }

  glPushMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  glColor4f(1.0F, 1.0F, 1.0F, alpha);

  glBegin(GL_QUADS);

  glTexCoord2f(0.0F, 1.0F);
  glVertex2f(position->x - height / 2.0F, position->y - height / 2.0F);

  glTexCoord2f(1.0F, 1.0F);
  glVertex2f(position->x + height / 2.0F, position->y - height / 2.0F);

  glTexCoord2f(1.0F, 0.0F);
  glVertex2f(position->x + height / 2.0F, position->y + height / 2.0F);

  glTexCoord2f(0.0F, 0.0F);
  glVertex2f(position->x - height / 2.0F, position->y + height / 2.0F);

  glEnd();

  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}
