// 作成者: j19426 西澤駿太郎
#include "bullet.h"

#include "opengl.h"

void bulletDrawDot(const bullet_t *bullet) {
  glPointSize(5.0F);
  glColor3ub(0xff, 0x00, 0x00);
  glBegin(GL_POINTS);
  glVertex2f(bullet->position.x, bullet->position.y);
  glEnd();
}
