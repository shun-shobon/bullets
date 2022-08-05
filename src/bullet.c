// 作成者: j19426 西澤駿太郎
#include "bullet.h"

#include "opengl.h"
#include "primitive.h"

void bulletDrawSquare(const bullet_t *bullet) {
  glColor3ub(0xff, 0x00, 0x00);
  glBegin(GL_QUADS);
  glVertex2f(bullet->position.x - bullet->size / 2,
             bullet->position.y - bullet->size / 2);
  glVertex2f(bullet->position.x + bullet->size / 2,
             bullet->position.y - bullet->size / 2);
  glVertex2f(bullet->position.x + bullet->size / 2,
             bullet->position.y + bullet->size / 2);
  glVertex2f(bullet->position.x - bullet->size / 2,
             bullet->position.y + bullet->size / 2);
  glEnd();
}

void bulletDrawCircle(const bullet_t *bullet) {
  glColor3ub(0xff, 0x00, 0x00);
  drawCircle(&bullet->position, bullet->size / 2, true);
}
