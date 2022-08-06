// 作成者: j19426 西澤駿太郎
#include "title.h"

#include "consts.h"
#include "effect.h"
#include "primitive.h"
#include "vector.h"

void titleInit(title_t *title) { title->age = 0; }
void titleUpdate(title_t *title) {
  gridDraw(&(vec2_t){0.0F, 0.0F}, &WINDOW_SIZE, title->age);
}
void titleDraw(const title_t *title) {
  drawTexture(&(vec2_t){WINDOW_SIZE.x / 2.0F, WINDOW_SIZE.y * 0.7F},
              WINDOW_SIZE.x, TEXTURE_TITLE);
}
