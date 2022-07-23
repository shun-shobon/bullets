// 作成者: j19426 西澤駿太郎
#include "enemy.h"

#include <stdio.h>

#include "consts.h"
#include "opengl.h"

VEC_IMPL(enemy_t)

int timeStart;
vec_enemy_t enemies;

void enemyMoveLiner(enemy_t *self, int timeDelta) {
  static const float MOVEMENT = 0.05F;

  self->position.y -= (float)timeDelta * MOVEMENT;
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

void enemiesInit() {
  timeStart = glutGet(GLUT_ELAPSED_TIME);
  vec_init_enemy_t(&enemies);
}

void enemiesUpdate(int timeDelta) {
  timeStart += timeDelta;

  for (size_t i = 0; i < enemies.len; i++) {
    enemies.ptr[i].move(&enemies.ptr[i], timeDelta);
  }

  // 以下は仮置
  // 3秒おきに敵を生成
  static int timeEnemySpawn = 0;
  timeEnemySpawn += timeDelta;

  if (3000 < timeEnemySpawn) {
    timeEnemySpawn = timeEnemySpawn - 3000;
    enemy_t newEnemy = {.position = {GAME_SIZE.x / 2, GAME_SIZE.y},
                        .age = 0,
                        .draw = enemyDrawSquare,
                        .move = enemyMoveLiner};
    vec_push_enemy_t(&enemies, newEnemy);
  }
}

void enemiesDraw() {
  for (size_t i = 0; i < enemies.len; i++) {
    enemies.ptr[i].draw(&enemies.ptr[i]);
  }
}
