// 作成者: j19426 西澤駿太郎
#include "event.h"

#include "opengl.h"

void handle_special_key_event(int raw_key, __attribute__((unused)) int x,
                              __attribute__((unused)) int y) {
  key_t key;

  switch (raw_key) {
    case GLUT_KEY_DOWN:
      key = KEY_DOWN;
      break;
    case GLUT_KEY_UP:
      key = KEY_UP;
      break;
    case GLUT_KEY_LEFT:
      key = KEY_LEFT;
      break;
    case GLUT_KEY_RIGHT:
      key = KEY_RIGHT;
      break;
    default:
      return;
  }
}
