// 作成者: j19426 西澤駿太郎
#include "event.h"

#include "opengl.h"

bool keyState[KEY_LENGTH];

// NOLINTNEXTLINE
void handleSpecialKeyDown(int rawKey, __attribute__((unused)) int x,
                          __attribute__((unused)) int y) {
  switch (rawKey) {
    case GLUT_KEY_DOWN:
      keyState[KEY_DOWN] = true;
      break;
    case GLUT_KEY_UP:
      keyState[KEY_UP] = true;
      break;
    case GLUT_KEY_LEFT:
      keyState[KEY_LEFT] = true;
      break;
    case GLUT_KEY_RIGHT:
      keyState[KEY_RIGHT] = true;
      break;
    default:
      return;
  }
}

// NOLINTNEXTLINE
void handleSpecialKeyUp(int rawKey, __attribute__((unused)) int x,
                        __attribute__((unused)) int y) {
  switch (rawKey) {
    case GLUT_KEY_DOWN:
      keyState[KEY_DOWN] = false;
      break;
    case GLUT_KEY_UP:
      keyState[KEY_UP] = false;
      break;
    case GLUT_KEY_LEFT:
      keyState[KEY_LEFT] = false;
      break;
    case GLUT_KEY_RIGHT:
      keyState[KEY_RIGHT] = false;
      break;
    default:
      return;
  }
}
