// 作成者: j19426 西澤駿太郎
#include "enemy.h"

#include "consts.h"
#include "opengl.h"

void enemyMoveLiner(enemy_t *self, int timeDelta) {
  self->age += timeDelta;

  static const float MOVEMENT = 0.05F;
  self->position.y -= (float)timeDelta * MOVEMENT;

  if (self->age > 5000) {
    self->shouldRemove = true;
  }
}

void enemyDrawSquare(enemy_t *self) {
  static const float SIZE = 10.0F;

  glColor3ub(0xff, 0xff, 0xff);
  glBegin(GL_QUADS);
  glVertex2f(self->position.x - SIZE, self->position.y - SIZE);
  glVertex2f(self->position.x + SIZE, self->position.y - SIZE);
  glVertex2f(self->position.x + SIZE, self->position.y + SIZE);
  glVertex2f(self->position.x - SIZE, self->position.y + SIZE);
  glEnd();
}

void enemyInit(enemies_t *enemies) { enemiesInit(enemies); }

void enemyUpdate(enemies_t *enemies, int timeDelta) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    node->item.move(&node->item, timeDelta);
  }

  enemiesGC(enemies);

  // 以下は仮置
  // 3秒おきに敵を生成
  static int timeEnemySpawn = 0;
  timeEnemySpawn += timeDelta;

  if (3000 < timeEnemySpawn) {
    timeEnemySpawn = timeEnemySpawn - 3000;
    enemy_t newEnemy = {.position = {GAME_SIZE.x / 2, GAME_SIZE.y},
                        .age = 0,
                        .draw = enemyDrawSquare,
                        .move = enemyMoveLiner};
    enemiesPushBack(enemies, newEnemy);
  }
}

void enemyDraw(enemies_t *enemies) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    node->item.draw(&node->item);
  }
}

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

void enemiesGC(enemies_t *enemies) {
  for (enemy_node_t *node = enemies->head; node; node = node->next) {
    if (node->item.shouldRemove) {
      enemy_node_t *prev = node->prev;
      enemiesPop(enemies, node);
      node = prev;
    }
    if (!node) break;
  }
}

void enemiesPop(enemies_t *enemies, enemy_node_t *node) {
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

void enemiesPushBack(enemies_t *enemies, enemy_t newEnemy) {
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
