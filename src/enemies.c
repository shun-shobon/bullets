// 作成者: j19426 西澤駿太郎
#include "enemies.h"

#include "bullets.h"
#include "consts.h"
#include "enemy.h"
#include "gamestate.h"
#include "util.h"

static void enemiesGC(enemies_t *enemies);
static void enemiesPop(enemies_t *enemies, enemy_node_t *node);
static bool isEnemyShotCollision(const enemy_t *enemy, const shot_t *shot);

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

void enemiesUpdate(enemies_t *enemies, bullets_t *bullets, shots_t *shots,
                   player_t *player, gamestate_t *gamestate) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    enemy_t *enemy = &node->item;
    enemyUpdate(enemy, bullets, player);

    int limit =
        shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
    for (int i = shots->head; i < limit; i++) {
      int idx = i % SHOT_MAX;
      shot_t *shot = &shots->buff[idx];
      if (shot->wasHit) continue;

      if (isEnemyShotCollision(enemy, shot)) {
        shot->wasHit = true;

        enemy->hp -= 1;
        if (enemy->hp == 0) {
          enemy->shouldRemove = true;
          gamestate->score += enemy->score;
          break;
        }
      }
    }
  }

  enemiesGC(enemies);
}

void enemiesDraw(const enemies_t *enemies) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    node->item.draw(&node->item);
  }
}

void enemiesPushBack(enemies_t *enemies, enemy_t newEnemy) {
  enemy_node_t *node = mallocSafe(sizeof(struct enemy_node));
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

static bool isEnemyShotCollision(const enemy_t *enemy, const shot_t *shot) {
  float distance = distanceSegmentSegment(&enemy->position, &enemy->velocity,
                                          &shot->position, &shot->velocity);
  return distance < enemy->size / 2 + SHOT_SIZE / 2;
}
