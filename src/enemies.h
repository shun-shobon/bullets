// 作成者: j19426 西澤駿太郎
#pragma once

#include "enemy.h"

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
  size_t len;
} enemies_t;

void enemiesInit(enemies_t *enemies);
void enemiesDrop(enemies_t *enemies);
void enemiesUpdate(enemies_t *enemies);
void enemiesDraw(const enemies_t *enemies);
