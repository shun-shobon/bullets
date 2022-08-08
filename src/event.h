// 作成者: j19426 西澤駿太郎
#include <stdbool.h>

typedef struct {
  bool isPress;
  bool isClicked;
} key_state_t;

typedef enum {
  KEY_OTHER,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_P,
  KEY_Z,
  KEY_LENGTH,
} key_code_t;

void eventInit();

void handleKeyDown(unsigned char rawKeyCode, int x, int y);
void handleKeyUp(unsigned char rawKeyCode, int x, int y);
void handleSpecialKeyDown(int glutKeyCode, int x, int y);
void handleSpecialKeyUp(int glutKeyCode, int x, int y);
bool isKeyPress(key_code_t keyCode);
bool isKeyClick(key_code_t keyCode);
