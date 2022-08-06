// 作成者: j19426 西澤駿太郎
#include "primitive.h"

#include <math.h>
#include <stdbool.h>

#include "opengl.h"
#include "texture.h"
#include "vector.h"

void drawCircle(const vec2_t *center, float radius, bool fill) {
  static int COUNT = 20;

  if (fill) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center->x, center->y);
  }
  for (int i = 0; i <= COUNT; i++) {
    float theta = 2.0F * (float)M_PI * (float)i / (float)COUNT;
    glVertex2f(center->x + radius * sinf(theta),
               center->y - radius * cosf(theta));
  }
  glEnd();
}

void drawSquare(const vec2_t *center, float size) {
  glBegin(GL_QUADS);
  glVertex2f(center->x - size / 2, center->y - size / 2);
  glVertex2f(center->x + size / 2, center->y - size / 2);
  glVertex2f(center->x + size / 2, center->y + size / 2);
  glVertex2f(center->x - size / 2, center->y + size / 2);
  glEnd();
}

void drawTexture(const vec2_t *center, float size, texture_key_t textureKey) {
  texture_t *texture = &textures[textureKey];

  glPushMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  glColor4ub(0xff, 0xff, 0xff, 0xff);

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
