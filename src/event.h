// 作成者: j19426 西澤駿太郎
typedef enum {
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
} key_t;

void handle_special_key_event(int raw_key, int x, int y);
