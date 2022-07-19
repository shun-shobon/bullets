// 作成者: j19426 西澤駿太郎
#include "player.h"

#include <math.h>

#include "event.h"
#include "opengl.h"

player_t player_global;

static void player_set_vector(player_t *player) {
  static const float MOVEMENT = 0.15F;

  int vertical = 0;
  if ((key_state[KEY_UP] && key_state[KEY_DOWN]) ||
      (!key_state[KEY_UP] && !key_state[KEY_DOWN])) {
    vertical = 0;
  } else if (key_state[KEY_UP] && !key_state[KEY_DOWN]) {
    vertical = 1;
  } else if (!key_state[KEY_UP] && key_state[KEY_DOWN]) {
    vertical = -1;
  }

  int horizontal = 0;
  if ((key_state[KEY_RIGHT] && key_state[KEY_LEFT]) ||
      (!key_state[KEY_RIGHT] && !key_state[KEY_LEFT])) {
    horizontal = 0;
  } else if (key_state[KEY_RIGHT] && !key_state[KEY_LEFT]) {
    horizontal = 1;
  } else if (!key_state[KEY_RIGHT] && key_state[KEY_LEFT]) {
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

void player_update(int time_delta) {
  player_t *player = &player_global;

  player_set_vector(player);

  vec2 move_amount = vec2_mul_scalar(&player->vector, (float)time_delta);
  player->position = vec2_add(&player->position, &move_amount);
}

void player_draw() {
  player_t *player = &player_global;

  float size = 10.0F;

  glColor3ub(0x00, 0xFF, 0x00);
  glBegin(GL_QUADS);
  glVertex2f(player->position.x - size, player->position.y - size);
  glVertex2f(player->position.x + size, player->position.y - size);
  glVertex2f(player->position.x + size, player->position.y + size);
  glVertex2f(player->position.x - size, player->position.y + size);
  glEnd();
}
