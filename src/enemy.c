// 作成者: j19426 西澤駿太郎
#include "enemy.h"

#include "opengl.h"

// 直線的な移動
void enemyMoveLiner(enemy_t *self) {
  static const float MOVEMENT = 1.0F;
  self->position.y -= MOVEMENT;

  // TODO(shun_shobon): 勝手に死ぬ
  if (self->age > 300) {
    self->shouldRemove = true;
  }
}

// 正方形描画
void enemyDrawSquare(enemy_t *self) {
  static const float SIZE = 10.0F;

  glColor3ub(0xff, 0xff, 0xff);
  glBegin(GL_QUADS);
  glVertex2f(self->position.x - SIZE, self->position.y - SIZE);
  glVertex2f(self->position.x + SIZE, self->position.y - SIZE);
  glVertex2f(self->position.x + SIZE, self->position.y + SIZE);
  glVertex2f(self->position.x - SIZE, self->position.y + SIZE);
  glEnd();
}
