// 作成者: j19426 西澤駿太郎
#include "enemies.h"

#include "bullets.h"
#include "consts.h"
#include "enemy.h"
#include "util.h"

static void enemiesGC(enemies_t *enemies);
static void enemiesPop(enemies_t *enemies, enemy_node_t *node);
static void enemiesPushBack(enemies_t *enemies, enemy_t newEnemy);

void enemiesInit(enemies_t *enemies) {
  enemies->head = NULL;
  enemies->tail = NULL;
  enemies->len = 0;
}

void enemiesDrop(enemies_t *enemies) {
  enemy_node_t *head = enemies->head;
  while (head) {
    enemiesPop(enemies, head);
    head = enemies->head;
  }
}

void enemiesUpdate(enemies_t *enemies, bullets_t *bullets) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    enemy_t *enemy = &node->item;
    enemy->age += 1;
    enemy->move(&node->item);
    enemy->bullet(&node->item, bullets);
  }

  enemiesGC(enemies);

  // TODO(shun_shobon): 自動的に敵が出てくるようにする
  static int enemySpawnCoolTime = 0;
  enemySpawnCoolTime += 1;
  if (100 < enemySpawnCoolTime) {
    enemySpawnCoolTime = 0;
    enemy_t newEnemy = {.position = {GAME_SIZE.x / 2, GAME_SIZE.y},
                        .age = 0,
                        .draw = enemyDrawSquare,
                        .bullet = enemyBulletNormal,
                        .move = enemyMoveLiner};
    enemiesPushBack(enemies, newEnemy);
  }
}

void enemiesDraw(const enemies_t *enemies) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    node->item.draw(&node->item);
  }
}

static void enemiesGC(enemies_t *enemies) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    if (node->item.shouldRemove) {
      enemy_node_t *prev = node->prev;
      enemiesPop(enemies, node);
      node = prev;
    }
    if (!node) break;
  }
}

static void enemiesPop(enemies_t *enemies, enemy_node_t *node) {
  if (node->prev) {
    node->prev->next = node->next;
  } else {
    enemies->head = node->next;
  }
  if (node->next) {
    node->next->prev = node->prev;
  } else {
    enemies->tail = node->prev;
  }

  free(node);
  enemies->len -= 1;
}

static void enemiesPushBack(enemies_t *enemies, enemy_t newEnemy) {
  enemy_node_t *node = malloc_safe(sizeof(struct enemy_node));
  node->item = newEnemy;
  node->prev = enemies->tail;
  node->next = NULL;

  if (enemies->tail) {
    enemies->tail->next = node;
  } else {
    enemies->head = node;
  }

  enemies->tail = node;
  enemies->len += 1;
}
