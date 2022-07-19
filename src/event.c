// 作成者: j19426 西澤駿太郎
#include "event.h"

#include "opengl.h"

bool key_state[KEY_LENGTH];

// NOLINTNEXTLINE
void handle_special_key_down(int raw_key, __attribute__((unused)) int x,
                             __attribute__((unused)) int y) {
  switch (raw_key) {
    case GLUT_KEY_DOWN:
      key_state[KEY_DOWN] = true;
      break;
    case GLUT_KEY_UP:
      key_state[KEY_UP] = true;
      break;
    case GLUT_KEY_LEFT:
      key_state[KEY_LEFT] = true;
      break;
    case GLUT_KEY_RIGHT:
      key_state[KEY_RIGHT] = true;
      break;
    default:
      return;
  }
}

// NOLINTNEXTLINE
void handle_special_key_up(int raw_key, __attribute__((unused)) int x,
                           __attribute__((unused)) int y) {
  switch (raw_key) {
    case GLUT_KEY_DOWN:
      key_state[KEY_DOWN] = false;
      break;
    case GLUT_KEY_UP:
      key_state[KEY_UP] = false;
      break;
    case GLUT_KEY_LEFT:
      key_state[KEY_LEFT] = false;
      break;
    case GLUT_KEY_RIGHT:
      key_state[KEY_RIGHT] = false;
      break;
    default:
      return;
  }
}
