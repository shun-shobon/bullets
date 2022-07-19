// 作成者: j19426 西澤駿太郎
#include <stdbool.h>

typedef enum {
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_LENGTH,
} key_t;

extern bool key_state[KEY_LENGTH];

void handle_special_key_down(int raw_key, int x, int y);
void handle_special_key_up(int raw_key, int x, int y);
