// 作成者: j19426 西澤駿太郎
#include "player.h"

#include <math.h>
#include <stdbool.h>

#include "bullets.h"
#include "consts.h"
#include "event.h"
#include "opengl.h"
#include "texture.h"
#include "vector.h"

static void playerSetVector(player_t *player);
static bool isPlayerBulletCollision(const player_t *player,
                                    const bullet_t *bullet);

void playerInit(player_t *player) {
  player->position.x = GAME_SIZE.x / 2;
  player->position.y = GAME_SIZE.y * 0.2F;
  player->vector.x = 0.0F;
  player->vector.y = 0.0F;
}

void playerUpdate(player_t *player, bullets_t *bullets, bool *isGameOver) {
  if (*isGameOver) return;

  playerSetVector(player);

  player->position = vec2Add(&player->position, &player->vector);

  // 画面外に行かないようにする
  if (player->position.x < 0) player->position.x = 0;
  if (player->position.y < 0) player->position.y = 0;
  if (GAME_SIZE.x < player->position.x) player->position.x = GAME_SIZE.x;
  if (GAME_SIZE.y < player->position.y) player->position.y = GAME_SIZE.y;

  // 敵弾との当たり判定
  int limit = bullets->head <= bullets->tail ? bullets->tail
                                             : bullets->tail + BULLETS_MAX;
  for (int i = bullets->head; i < limit; i++) {
    int idx = i % BULLETS_MAX;
    bullet_t *bullet = &bullets->buff[idx];
    if (isPlayerBulletCollision(player, bullet)) {
      bullet->wasHit = true;
      *isGameOver = true;
      player->vector.x = 0;
      player->vector.y = 0;
    }
  }
}

void playerDraw(const player_t *player, bool isGameOver) {
  if (isGameOver) return;

  static const float size = 40.0F;

  drawTexture(&player->position, size, 1.0F, TEXTURE_PLAYER);

  glColor3ub(0xff, 0xff, 0x00);
}

static void playerSetVector(player_t *player) {
  int vertical = 0;
  if ((isKeyPress(KEY_UP) && isKeyPress(KEY_DOWN)) ||
      (!isKeyPress(KEY_UP) && !isKeyPress(KEY_DOWN))) {
    vertical = 0;
  } else if (isKeyPress(KEY_UP) && !isKeyPress(KEY_DOWN)) {
    vertical = 1;
  } else if (!isKeyPress(KEY_UP) && isKeyPress(KEY_DOWN)) {
    vertical = -1;
  }

  int horizontal = 0;
  if ((isKeyPress(KEY_RIGHT) && isKeyPress(KEY_LEFT)) ||
      (!isKeyPress(KEY_RIGHT) && !isKeyPress(KEY_LEFT))) {
    horizontal = 0;
  } else if (isKeyPress(KEY_RIGHT) && !isKeyPress(KEY_LEFT)) {
    horizontal = 1;
  } else if (!isKeyPress(KEY_RIGHT) && isKeyPress(KEY_LEFT)) {
    horizontal = -1;
  }

  float movement = PLAYER_MOVEMENT;
  float amount = vertical && horizontal ? sqrtf(3.0F) / 2.0F : 1;
  switch (vertical) {
    case 1:
      player->vector.y = movement * amount;
      break;
    case 0:
      player->vector.y = 0;
      break;
    case -1:
      player->vector.y = -movement * amount;
      break;
  }
  switch (horizontal) {
    case 1:
      player->vector.x = movement * amount;
      break;
    case 0:
      player->vector.x = 0;
      break;
    case -1:
      player->vector.x = -movement * amount;
      break;
  }
}

static bool isPlayerBulletCollision(const player_t *player,
                                    const bullet_t *bullet) {
  float distance = distanceSegmentSegment(&player->position, &player->vector,
                                          &bullet->position, &bullet->velocity);
  return distance < PLAYER_SIZE / 2 + bullet->size / 2;
}
