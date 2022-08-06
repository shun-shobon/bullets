// 作成者: j19426 西澤駿太郎
#include "spawner.h"

#include <stdlib.h>

#include "consts.h"
#include "enemies.h"
#include "enemy.h"
#include "util.h"
#include "vector.h"

static int getNextSpawnAge(int age);
static vec2_t getRandomSpawnPosition();
static float getRandomYVelocity();

void spawnerInit(spawner_t *spawner) {
  spawner->nextSpawnAge = getNextSpawnAge(0);
}

void spawnerUpdate(spawner_t *spawner, enemies_t *enemies, int age) {
  if (spawner->nextSpawnAge != age) return;
  spawner->nextSpawnAge = getNextSpawnAge(age);

  vec2_t position = getRandomSpawnPosition();
  float yVelocity = getRandomYVelocity();
  enemy_move_func_t move = getRandomEnemyMoveFunc();
  enemy_bullet_func_t bullet = getRandomEnemyBulletFunc();
  enemy_draw_func_t draw = getRandomEnemyDrawFunc();

  enemy_t enemy = enemyNew(position, yVelocity, 20.0F, 10, move, bullet, draw);
  enemiesPushBack(enemies, enemy);
}

static int getNextSpawnAge(int age) {
  return age + SPAWN_INTERVAL_MIN +
         (int)(random() % (SPAWN_INTERVAL_MAX - SPAWN_INTERVAL_MIN));
}

static vec2_t getRandomSpawnPosition() {
  float x = (float)(random() % (long)GAME_SIZE.x);
  float y = GAME_SIZE.y + 50.0F;

  return (vec2_t){x, y};
}

static float getRandomYVelocity() { return 0.5F + randomf() * 1.5F; }
