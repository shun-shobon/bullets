// 作成者: j19426 西澤駿太郎
#include "spawner.h"

#include <stdbool.h>
#include <stdlib.h>

#include "consts.h"
#include "enemies.h"
#include "enemy.h"
#include "stats.h"
#include "util.h"
#include "vector.h"

static int getNextSpawnAge(const stats_t *gamestate);
static vec2_t getRandomSpawnPosition();
static float getRandomYVelocity(const stats_t *gamestate);
static int getRandomScore(const stats_t *gamestate);

void spawnerInit(spawner_t *spawner, const stats_t *gamestate) {
  spawner->nextSpawnAge = getNextSpawnAge(gamestate);
}

void spawnerUpdate(spawner_t *spawner, enemies_t *enemies,
                   const stats_t *gamestate, bool isGameOver) {
  if (isGameOver) return;
  if (spawner->nextSpawnAge != gamestate->age) return;
  spawner->nextSpawnAge = getNextSpawnAge(gamestate);

  vec2_t position = getRandomSpawnPosition();
  float yVelocity = getRandomYVelocity(gamestate);
  int score = getRandomScore(gamestate);
  enemy_move_func_t move = getRandomEnemyMoveFunc();
  enemy_bullet_func_t bullet = getRandomEnemyBulletFunc();
  enemy_draw_func_t draw = getRandomEnemyDrawFunc();

  enemy_t enemy =
      enemyNew(position, yVelocity, 30.0F, 10, score, move, bullet, draw);
  enemiesPushBack(enemies, enemy);
}

static int getNextSpawnAge(const stats_t *gamestate) {
  return gamestate->age + SPAWN_INTERVAL_MIN +
         (int)(expRandomNormalizedf((float)(gamestate->level + 1)) *
               (float)(SPAWN_INTERVAL_MAX - SPAWN_INTERVAL_MIN));
}

static vec2_t getRandomSpawnPosition() {
  float x = (float)(random() % (long)GAME_SIZE.x);
  float y = GAME_SIZE.y + 50.0F;

  return (vec2_t){x, y};
}

static float getRandomYVelocity(const stats_t *gamestate) {
  return 0.5F +
         (1 - expRandomNormalizedf((float)(gamestate->level + 1))) * 2.0F;
}

static int getRandomScore(const stats_t *gamestate) {
  return 50 + (int)((1 - expRandomNormalizedf((float)(gamestate->level + 1))) *
                    45.0F) *
                  10;
}
