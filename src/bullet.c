// 作成者: j19426 西澤駿太郎
#include "bullet.h"

#include "opengl.h"
#include "primitive.h"

void bulletDrawSquare(const bullet_t *bullet) {
  glColor3ub(0xff, 0x00, 0x00);
  drawSquare(&bullet->position, bullet->size);
}

void bulletDrawCircle(const bullet_t *bullet) {
  glColor3ub(0xff, 0x00, 0x00);
  drawCircle(&bullet->position, bullet->size / 2, true);
}
