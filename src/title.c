// 作成者: j19426 西澤駿太郎
#include "title.h"

#include "consts.h"
#include "effect.h"
#include "event.h"
#include "primitive.h"
#include "vector.h"

void titleInit(title_t *title) { title->age = 0; }

void titleDrop(__attribute__((unused)) title_t *title) {}

void titleUpdate(title_t *title, phase_t *moveNextPhase) {
  title->age += 1;

  gridDraw(&(vec2_t){0.0F, 0.0F}, &WINDOW_SIZE, title->age);

  if (keyState[KEY_Z]) {
    *moveNextPhase = PHASE_GAME;
  }
}

void titleDraw(__attribute__((unused)) const title_t *title) {
  drawTexture(&(vec2_t){WINDOW_SIZE.x / 2.0F, WINDOW_SIZE.y * 0.7F},
              WINDOW_SIZE.x, TEXTURE_TITLE);
}