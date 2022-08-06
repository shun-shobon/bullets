// 作成者: j19426 西澤駿太郎
#include "event.h"

#include <stdbool.h>

#include "opengl.h"

bool keyState[KEY_LENGTH];

static void handleKey(unsigned char rawKeyCode, bool isDown);
static void handleSpecialKey(int rawKey, bool isDown);
static void handleModifierKey();

void eventInit() {
  for (int i = 0; i < KEY_LENGTH; i++) {
    keyState[i] = false;
  }
}

void handleKeyDown(unsigned char rawKeyCode, __attribute__((unused)) int x,
                   __attribute__((unused)) int y) {
  handleKey(rawKeyCode, true);
}

void handleKeyUp(unsigned char rawKeyCode, __attribute__((unused)) int x,
                 __attribute__((unused)) int y) {
  handleKey(rawKeyCode, false);
}

void handleSpecialKeyDown(int rawKey, __attribute__((unused)) int x,
                          __attribute__((unused)) int y) {
  handleSpecialKey(rawKey, true);
}

void handleSpecialKeyUp(int rawKey, __attribute__((unused)) int x,
                        __attribute__((unused)) int y) {
  handleSpecialKey(rawKey, false);
}

static void handleKey(unsigned char rawKeyCode, bool isDown) {
  switch (rawKeyCode) {
    case 'z':
    case 'Z':
      keyState[KEY_Z] = isDown;
      break;
    case 'x':
    case 'X':
      keyState[KEY_X] = isDown;
      break;
    case 'q':
    case 'Q':
      keyState[KEY_Q] = isDown;
      break;
  }

  handleModifierKey();
}

void handleSpecialKey(int rawKey, bool isDown) {
  switch (rawKey) {
    case GLUT_KEY_DOWN:
      keyState[KEY_DOWN] = isDown;
      break;
    case GLUT_KEY_UP:
      keyState[KEY_UP] = isDown;
      break;
    case GLUT_KEY_LEFT:
      keyState[KEY_LEFT] = isDown;
      break;
    case GLUT_KEY_RIGHT:
      keyState[KEY_RIGHT] = isDown;
      break;
  }

  handleModifierKey();
}

static void handleModifierKey() {
  int modifiers = glutGetModifiers();
  keyState[KEY_SHIFT] = (bool)(modifiers & GLUT_ACTIVE_SHIFT);
}
