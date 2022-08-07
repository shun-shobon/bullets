// 作成者: j19426 西澤駿太郎
#include "title.h"

#include <stdlib.h>

#include "consts.h"
#include "effect.h"
#include "event.h"
#include "select.h"
#include "texture.h"
#include "vector.h"

void titleInit(title_t *title) {
  title->age = 0;
  selectInit(&title->select, "START", "QUIT", NULL);
}

void titleDrop(title_t *title) { selectDrop(&title->select); }

void titleUpdate(title_t *title, phase_t *moveNextPhase) {
  title->age += 1;

  selectUpdate(&title->select);
  switch (title->select.selected) {
    case 0:
      *moveNextPhase = PHASE_GAME;
      break;
    case 1:
      exit(0);
  }
}

void titleDraw(const title_t *title) {
  gridDraw(&(vec2_t){0.0F, 0.0F}, &WINDOW_SIZE, title->age);

  drawTexture(&(vec2_t){WINDOW_SIZE.x / 2.0F, WINDOW_SIZE.y * 0.7F},
              WINDOW_SIZE.x, 1.0F, TEXTURE_TITLE);
  selectDraw(&title->select, title->age,
             &(vec2_t){WINDOW_SIZE.x / 2.0F, WINDOW_SIZE.y * 0.3F}, 30.0F,
             30.0F);
}
