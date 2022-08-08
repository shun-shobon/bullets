// 作成者: j19426 西澤駿太郎
#include "event.h"

#include <stdbool.h>

#include "opengl.h"

static key_state_t keyState[KEY_LENGTH];

static key_code_t getKeyFromChar(unsigned char rawKeyCode);
static key_code_t getKeyFromGlutKeyCode(int glutKeyCode);

void eventInit() {
  for (int i = 0; i < KEY_LENGTH; i++) {
    keyState[i].isPress = false;
    keyState[i].isClicked = false;
  }
}

void handleKeyDown(unsigned char rawKeyCode, __attribute__((unused)) int x,
                   __attribute__((unused)) int y) {
  keyState[getKeyFromChar(rawKeyCode)].isPress = true;
}

void handleKeyUp(unsigned char rawKeyCode, __attribute__((unused)) int x,
                 __attribute__((unused)) int y) {
  keyState[getKeyFromChar(rawKeyCode)].isPress = false;
  keyState[getKeyFromChar(rawKeyCode)].isClicked = false;
}

void handleSpecialKeyDown(int glutKeyCode, __attribute__((unused)) int x,
                          __attribute__((unused)) int y) {
  keyState[getKeyFromGlutKeyCode(glutKeyCode)].isPress = true;
}

void handleSpecialKeyUp(int glutKeyCode, __attribute__((unused)) int x,
                        __attribute__((unused)) int y) {
  keyState[getKeyFromGlutKeyCode(glutKeyCode)].isPress = false;
  keyState[getKeyFromGlutKeyCode(glutKeyCode)].isClicked = false;
}

bool isKeyPress(key_code_t keyCode) {
  if (keyState[keyCode].isPress) {
    keyState[keyCode].isClicked = true;
    return true;
  }
  return false;
}

bool isKeyClick(key_code_t keyCode) {
  if (keyState[keyCode].isPress && !keyState[keyCode].isClicked) {
    keyState[keyCode].isClicked = true;
    return true;
  }
  return false;
}

static key_code_t getKeyFromChar(unsigned char rawKeyCode) {
  switch (rawKeyCode) {
    case 'p':
    case 'P':
      return KEY_P;
    case 'z':
    case 'Z':
      return KEY_Z;
    default:
      return KEY_OTHER;
  }
}

static key_code_t getKeyFromGlutKeyCode(int glutKeyCode) {
  switch (glutKeyCode) {
    case GLUT_KEY_DOWN:
      return KEY_DOWN;
    case GLUT_KEY_UP:
      return KEY_UP;
    case GLUT_KEY_LEFT:
      return KEY_LEFT;
    case GLUT_KEY_RIGHT:
      return KEY_RIGHT;
    default:
      return KEY_OTHER;
  }
}
