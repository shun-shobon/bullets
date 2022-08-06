// 作成者: j19426 西澤駿太郎
#pragma once

#include "bullets.h"
#include "enemy.h"
#include "player.h"
#include "shots.h"
#include "stats.h"

struct enemy_node {
  enemy_t item;
  struct enemy_node *prev;
  struct enemy_node *next;
};
typedef struct enemy_node enemy_node_t;

// 双方向連結リスト
typedef struct {
  struct enemy_node *head;
  struct enemy_node *tail;
  int len;
} enemies_t;

void enemiesInit(enemies_t *enemies);
void enemiesDrop(enemies_t *enemies);
void enemiesUpdate(enemies_t *enemies, bullets_t *bullets, shots_t *shots,
                   player_t *player, stats_t *stats);
void enemiesDraw(const enemies_t *enemies);
void enemiesPushBack(enemies_t *enemies, enemy_t newEnemy);
