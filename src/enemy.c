// 作成者: j19426 西澤駿太郎
#include "enemy.h"

#include "opengl.h"

void enemyMoveLiner(enemy_t *self, int timeDelta) {
  self->age += timeDelta;

  static const float MOVEMENT = 0.05F;
  self->position.y -= (float)timeDelta * MOVEMENT;

  if (self->age > 5000) {
    self->shouldRemove = true;
  }
}

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
