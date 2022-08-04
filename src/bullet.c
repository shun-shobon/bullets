// 作成者: j19426 西澤駿太郎
#include "bullet.h"

#include "opengl.h"

void bulletDrawDot(bullet_t *bullet) {
  glPointSize(5.0F);
  glBegin(GL_POINTS);
  glVertex2f(bullet->position.x, bullet->position.y);
  glEnd();
}
