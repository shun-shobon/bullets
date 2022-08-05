// 作成者: j19426 西澤駿太郎
#include <stdbool.h>

typedef enum {
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_SHIFT,
  KEY_Q,
  KEY_Z,
  KEY_LENGTH,
} key_t;

extern bool keyState[KEY_LENGTH];

void eventInit();

void handleKeyDown(unsigned char rawKeyCode, int x, int y);
void handleKeyUp(unsigned char rawKeyCode, int x, int y);
void handleSpecialKeyDown(int rawKey, int x, int y);
void handleSpecialKeyUp(int rawKey, int x, int y);
