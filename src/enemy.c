// 作成者: j19426 西澤駿太郎
#include "enemy.h"

#include <stdlib.h>

#include "bullet.h"
#include "bullets.h"
#include "opengl.h"
#include "primitive.h"

void enemyUpdate(enemy_t *enemy, bullets_t *bullets) {
  enemy->age += 1;
  enemy->move(enemy);
  enemy->bullet(enemy, bullets);
}

const enemy_move_func_t enemyMoveFuncs[] = {enemyMoveLiner};
const enemy_bullet_func_t enemyBulletFuncs[] = {enemyBulletNormal};
const enemy_draw_func_t enemyDrawFuncs[] = {enemyDrawSquare};

enemy_move_func_t getRandomEnemyMoveFunc() {
  return enemyMoveFuncs[random() % ENEMY_MOVE_FUNCS];
}
enemy_bullet_func_t getRandomEnemyBulletFunc() {
  return enemyBulletFuncs[random() % ENEMY_BULLET_FUNCS];
}
enemy_draw_func_t getRandomEnemyDrawFunc() {
  return enemyDrawFuncs[random() % ENEMY_DRAW_FUNCS];
}

// 直線的な移動
void enemyMoveLiner(enemy_t *self) {
  static const float MOVEMENT = 1.0F;
  self->position.y -= MOVEMENT;
  self->velocity.y = -MOVEMENT;
}

// ノーマル弾発射
void enemyBulletNormal(enemy_t *self, bullets_t *bullets) {
  if (self->age % 10 == 0) {
    bullet_t bullet = bulletNew(self->position, (vec2_t){0.0F, -5.0F}, 5.0F,
                                bulletDrawCircle);
    bulletsPushBack(bullets, bullet);
  }
}

// 正方形描画
void enemyDrawSquare(enemy_t *self) {
  glColor3ub(0xff, 0xff, 0xff);
  drawSquare(&self->position, self->size);
}
