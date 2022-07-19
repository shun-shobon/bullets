// 作成者: j19426 西澤駿太郎
#include "player.h"

#include <math.h>

#include "consts.h"
#include "event.h"
#include "opengl.h"

player_t playerGlobal;

static void playerSetVector(player_t *player) {
  static const float MOVEMENT = 0.15F;

  int vertical = 0;
  if ((keyState[KEY_UP] && keyState[KEY_DOWN]) ||
      (!keyState[KEY_UP] && !keyState[KEY_DOWN])) {
    vertical = 0;
  } else if (keyState[KEY_UP] && !keyState[KEY_DOWN]) {
    vertical = 1;
  } else if (!keyState[KEY_UP] && keyState[KEY_DOWN]) {
    vertical = -1;
  }

  int horizontal = 0;
  if ((keyState[KEY_RIGHT] && keyState[KEY_LEFT]) ||
      (!keyState[KEY_RIGHT] && !keyState[KEY_LEFT])) {
    horizontal = 0;
  } else if (keyState[KEY_RIGHT] && !keyState[KEY_LEFT]) {
    horizontal = 1;
  } else if (!keyState[KEY_RIGHT] && keyState[KEY_LEFT]) {
    horizontal = -1;
  }

  float amount = vertical && horizontal ? sqrtf(3.0F) / 2.0F : 1;
  switch (vertical) {
    case 1:
      player->vector.y = MOVEMENT * amount;
      break;
    case 0:
      player->vector.y = 0;
      break;
    case -1:
      player->vector.y = -MOVEMENT * amount;
      break;
  }
  switch (horizontal) {
    case 1:
      player->vector.x = MOVEMENT * amount;
      break;
    case 0:
      player->vector.x = 0;
      break;
    case -1:
      player->vector.x = -MOVEMENT * amount;
      break;
  }
}

void playerUpdate(int timeDelta) {
  player_t *player = &playerGlobal;

  playerSetVector(player);

  vec2_t moveAmount = vec2MulScalar(&player->vector, (float)timeDelta);
  player->position = vec2Add(&player->position, &moveAmount);

  // 画面外に行かないようにする
  if (player->position.x < 0) {
    player->position.x = 0;
  }
  if (GAME_SIZE.x < player->position.x) {
    player->position.x = GAME_SIZE.x;
  }
  if (player->position.y < 0) {
    player->position.y = 0;
  }
  if (GAME_SIZE.y < player->position.y) {
    player->position.y = GAME_SIZE.y;
  }
}

void playerDraw() {
  player_t *player = &playerGlobal;

  float size = 10.0F;

  glColor3ub(0x00, 0xFF, 0x00);
  glBegin(GL_QUADS);
  glVertex2f(player->position.x - size, player->position.y - size);
  glVertex2f(player->position.x + size, player->position.y - size);
  glVertex2f(player->position.x + size, player->position.y + size);
  glVertex2f(player->position.x - size, player->position.y + size);
  glEnd();
}
