// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "bullets.h"
#include "player.h"
#include "vector.h"

struct enemy {
  vec2_t spawnPosition;
  vec2_t position;
  float yVelocity;
  vec2_t velocity;
  float size;
  int age;
  int hp;
  int maxHp;
  int score;
  void (*move)(struct enemy *self);
  void (*bullet)(struct enemy *self, bullets_t *bullets, player_t *player);
  void (*draw)(struct enemy *self);
  bool shouldRemove;
};
typedef struct enemy enemy_t;
typedef void (*enemy_move_func_t)(enemy_t *self);
typedef void (*enemy_bullet_func_t)(enemy_t *self, bullets_t *bullets,
                                    player_t *player);
typedef void (*enemy_draw_func_t)(enemy_t *self);

static inline enemy_t enemyNew(vec2_t position, float yVelocity, float size,
                               int hp, int score, enemy_move_func_t move,
                               enemy_bullet_func_t bullet,
                               enemy_draw_func_t draw) {
  return (enemy_t){.spawnPosition = position,
                   .position = position,
                   .yVelocity = yVelocity,
                   .velocity = {0.0F, 0.0F},
                   .size = size,
                   .age = 0,
                   .hp = hp,
                   .maxHp = hp,
                   .score = score,
                   .move = move,
                   .bullet = bullet,
                   .draw = draw,
                   .shouldRemove = false};
}

void enemyUpdate(enemy_t *enemy, bullets_t *bullets, player_t *player);

#define ENEMY_MOVE_FUNCS 2
#define ENEMY_BULLET_FUNCS 5
#define ENEMY_DRAW_FUNCS 1

extern const enemy_move_func_t enemyMoveFuncs[];
extern const enemy_bullet_func_t enemyBulletFuncs[];
extern const enemy_draw_func_t enemyDrawFuncs[];

enemy_move_func_t getRandomEnemyMoveFunc();
enemy_bullet_func_t getRandomEnemyBulletFunc();
enemy_draw_func_t getRandomEnemyDrawFunc();
