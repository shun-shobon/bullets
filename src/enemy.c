// 作成者: j19426 西澤駿太郎
#include "enemy.h"

#include <math.h>
#include <stdlib.h>

#include "bullet.h"
#include "bullets.h"
#include "opengl.h"
#include "primitive.h"

static void enemyMoveLiner(enemy_t *self);
static void enemyMoveWave(enemy_t *self);
static void enemyBulletStraight(enemy_t *self, bullets_t *bullets,
                                player_t *player);
static void enemyBulletFan(enemy_t *self, bullets_t *bullets, player_t *player);
static void enemyBulletCircle(enemy_t *self, bullets_t *bullets,
                              player_t *player);
static void enemyBulletOddStraight(enemy_t *self, bullets_t *bullets,
                                   player_t *player);
static void enemyBulletOddFan(enemy_t *self, bullets_t *bullets,
                              player_t *player);
static void enemyDrawSquare(enemy_t *self);

void enemyUpdate(enemy_t *enemy, bullets_t *bullets, player_t *player) {
  enemy->move(enemy);
  enemy->bullet(enemy, bullets, player);
  enemy->age += 1;

  if (enemy->position.y < -100) {
    enemy->shouldRemove = true;
  }
}

const enemy_move_func_t enemyMoveFuncs[] = {enemyMoveLiner, enemyMoveWave};
const enemy_bullet_func_t enemyBulletFuncs[] = {
    enemyBulletStraight, enemyBulletFan, enemyBulletCircle,
    enemyBulletOddStraight, enemyBulletOddFan};
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
static void enemyMoveLiner(enemy_t *self) {
  self->position.y -= self->yVelocity;
  self->velocity.y = -self->yVelocity;
}

// 波打った移動
static void enemyMoveWave(enemy_t *self) {
  static const float CYCLE = 50.0F;
  static const float MOVEMENT_X_MAX = 40.0F;

  self->position.y -= self->yVelocity;
  self->velocity.y = -self->yVelocity;

  float theta = self->position.y * (float)M_PI / CYCLE;
  float x = self->spawnPosition.x + MOVEMENT_X_MAX * sinf(theta);
  self->velocity.x = x - self->position.x;
  self->position.x = x;
}

// 直線弾発射
static void enemyBulletStraight(enemy_t *self, bullets_t *bullets,
                                __attribute__((unused)) player_t *player) {
  if (self->age % 20 != 0) return;

  bullet_t bullet =
      bulletNew(self->position, (vec2_t){0.0F, -3.0F}, 5.0F, bulletDrawSquare);
  bulletsPushBack(bullets, bullet);
}

// 扇弾発射
static void enemyBulletFan(enemy_t *self, bullets_t *bullets,
                           __attribute__((unused)) player_t *player) {
  static const float VELOCITY = 3.0F;
  static const float ANGLE = 30.0F * 2.0F * (float)M_PI / 360.0F;

  if (self->age % 60 != 0) return;

  bullet_t bulletCenter = bulletNew(self->position, (vec2_t){0.0F, -VELOCITY},
                                    5.0F, bulletDrawSquare);
  bullet_t bulletRight = bulletNew(
      self->position, (vec2_t){VELOCITY * sinf(ANGLE), -VELOCITY * cosf(ANGLE)},
      5.0F, bulletDrawSquare);
  bullet_t bulletLeft =
      bulletNew(self->position,
                (vec2_t){VELOCITY * sinf(-ANGLE), -VELOCITY * cosf(-ANGLE)},
                5.0F, bulletDrawSquare);

  bulletsPushBack(bullets, bulletCenter);
  bulletsPushBack(bullets, bulletRight);
  bulletsPushBack(bullets, bulletLeft);
}

// 円形弾発射
static void enemyBulletCircle(enemy_t *self, bullets_t *bullets,
                              __attribute__((unused)) player_t *player) {
  static const float VELOCITY = 3.0F;
  static const int AMOUNT = 8;

  if (self->age % 80 != 0) return;

  for (int i = 0; i < AMOUNT; i++) {
    float theta = (float)i * 2.0F * (float)M_PI / (float)AMOUNT;
    vec2_t velocity = {VELOCITY * sinf(theta), VELOCITY * cosf(theta)};
    bullet_t bullet =
        bulletNew(self->position, velocity, 5.0F, bulletDrawSquare);
    bulletsPushBack(bullets, bullet);
  }
}

// 奇数弾発射
static void enemyBulletOddStraight(enemy_t *self, bullets_t *bullets,
                                   player_t *player) {
  static const float VELOCITY = 3.0F;

  if (self->age % 30 != 0) return;

  vec2_t enemyPlayerVector = vec2Sub(&player->position, &self->position);
  vec2_t enemyPlayerVectorNormalized = vec2Normalize(&enemyPlayerVector);
  vec2_t velocity = vec2MulScalar(&enemyPlayerVectorNormalized, VELOCITY);
  bullet_t bullet = bulletNew(self->position, velocity, 5.0F, bulletDrawSquare);
  bulletsPushBack(bullets, bullet);
}

// 奇数扇弾発射
static void enemyBulletOddFan(enemy_t *self, bullets_t *bullets,
                              player_t *player) {
  static const float VELOCITY = 3.0F;
  static const float ANGLE = 15.0F * 2.0F * (float)M_PI / 360.0F;

  if (self->age % 60 != 0) return;

  vec2_t enemyPlayerVector = vec2Sub(&player->position, &self->position);
  vec2_t enemyPlayerVectorNormalized = vec2Normalize(&enemyPlayerVector);

  vec2_t velocityCenter = vec2MulScalar(&enemyPlayerVectorNormalized, VELOCITY);
  vec2_t velocityRight = {
      velocityCenter.x * cosf(ANGLE) - velocityCenter.y * sinf(ANGLE),
      velocityCenter.x * sinf(ANGLE) + velocityCenter.y * cosf(ANGLE)};
  vec2_t velocityLeft = {
      velocityCenter.x * cosf(-ANGLE) - velocityCenter.y * sinf(-ANGLE),
      velocityCenter.x * sinf(-ANGLE) + velocityCenter.y * cosf(-ANGLE)};
  bullet_t bulletCenter =
      bulletNew(self->position, velocityCenter, 5.0F, bulletDrawSquare);
  bullet_t bulletRight =
      bulletNew(self->position, velocityRight, 5.0F, bulletDrawSquare);
  bullet_t bulletLeft =
      bulletNew(self->position, velocityLeft, 5.0F, bulletDrawSquare);
  bulletsPushBack(bullets, bulletCenter);
  bulletsPushBack(bullets, bulletRight);
  bulletsPushBack(bullets, bulletLeft);
}

// 正方形描画
static void enemyDrawSquare(enemy_t *self) {
  glColor3ub(0xff, 0xff, 0xff);
  drawSquare(&self->position, self->size);
}
