// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

#include "primitive.h"
#include "util.h"

struct enemy {
  vec2_t position;
  int age;
  void (*draw)(struct enemy *self);
  void (*move)(struct enemy *self, int timeDelta);
  bool shouldRemove;
};
typedef struct enemy enemy_t;

struct enemy_node {
  enemy_t item;
  struct enemy_node *prev;
  struct enemy_node *next;
};
typedef struct enemy_node enemy_node_t;

typedef struct {
  struct enemy_node *head;
  struct enemy_node *tail;
  size_t len;
} enemies_t;

void enemyInit(enemies_t *enemies);
void enemyUpdate(enemies_t *enemies, int timeDelta);
void enemyDraw(enemies_t *enemies);

void enemiesInit(enemies_t *enemies);
void enemiesDrop(enemies_t *enemies);
void enemiesGC(enemies_t *enemies);
void enemiesPop(enemies_t *enemies, enemy_node_t *node);
void enemiesPushBack(enemies_t *enemies, enemy_t newEnemy);
