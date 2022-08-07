// 作成者: j19426 西澤駿太郎
#include "global.h"

#include "consts.h"
#include "event.h"
#include "game.h"
#include "title.h"

static void movePhase(global_t *global, phase_t src, phase_t dst);

void globalInit(global_t *global) {
  global->phase = PHASE_TITLE;
  global->moveNextPhase = PHASE_NONE;
  global->isPause = false;
  titleInit(&global->title);
}

void globalUpdate(global_t *global) {
  if (isKeyPress(KEY_P)) global->isPause = !global->isPause;
  if (global->isPause) return;

  if (global->moveNextPhase != PHASE_NONE) {
    movePhase(global, global->phase, global->moveNextPhase);
  }

  switch (global->phase) {
    case PHASE_TITLE:
      titleUpdate(&global->title, &global->moveNextPhase);
      break;
    case PHASE_GAME:
      gameUpdate(&global->game, &global->moveNextPhase);
      break;
    case PHASE_NONE:
      // Unreachable
      break;
  }
}

void globalDraw(const global_t *global) {
  switch (global->phase) {
    case PHASE_TITLE:
      titleDraw(&global->title);
      break;
    case PHASE_GAME:
      gameDraw(&global->game);
      break;
    case PHASE_NONE:
      // Unreachable
      break;
  }
}

static void movePhase(global_t *global, phase_t src, phase_t dst) {
  switch (src) {
    case PHASE_TITLE:
      titleDrop(&global->title);
      break;
    case PHASE_GAME:
      gameDrop(&global->game);
      break;
    case PHASE_NONE:
      // Unreachable
      break;
  }

  switch (dst) {
    case PHASE_TITLE:
      titleInit(&global->title);
      break;
    case PHASE_GAME:
      gameInit(&global->game);
      break;
    case PHASE_NONE:
      // Unreachable
      break;
  }

  global->phase = dst;
  global->moveNextPhase = PHASE_NONE;
}
