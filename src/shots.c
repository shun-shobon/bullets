// 作成者: j19426 西澤駿太郎
#include "shots.h"

#include "consts.h"
#include "event.h"
#include "opengl.h"
#include "player.h"
#include "primitive.h"
#include "vector.h"

static void shotsPushBack(shots_t *shots, shot_t shot);
static void shotDraw(const shot_t *shot);

void shotsInit(shots_t *shots) {
  shots->head = 0;
  shots->tail = 0;
  shots->coolTime = 0;
}

void shotsUpdate(shots_t *shots, const player_t *player) {
  shots->coolTime += 1;
  if (keyState[KEY_Z] && SHOT_INTERVAL < shots->coolTime) {
    vec2_t vector = {0.0F, SHOT_MOVEMENT};
    shot_t shot = {
        .position = player->position, .vector = vector, .didHit = false};
    shotsPushBack(shots, shot);
    shots->coolTime = 0;
  }

  int limit = shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
  for (int i = shots->head; i < limit; i++) {
    int idx = i % SHOT_MAX;
    shot_t *shot = &shots->buff[idx];
    shot->position = vec2Add(&shot->position, &shot->vector);
  }
}

void shotsDraw(const shots_t *shots) {
  int limit = shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
  for (int i = shots->head; i < limit; i++) {
    int idx = i % SHOT_MAX;
    const shot_t *shot = &shots->buff[idx];

    if (shot->didHit) continue;

    shotDraw(shot);
  }
}

static void shotsPushBack(shots_t *shots, shot_t shot) {
  shots->buff[shots->tail] = shot;
  shots->tail += 1;
  if (SHOT_MAX <= shots->tail) {
    shots->tail = 0;
  }

  // キューから溢れたら一番古い弾を消す
  if (shots->head == shots->tail) {
    shots->head += 1;
    if (SHOT_MAX <= shots->head) {
      shots->head = 0;
    }
  }
}

static void shotDraw(const shot_t *shot) {
  glColor3ub(0x55, 0xaa, 0x55);
  drawSquare(&shot->position, SHOT_SIZE);
}
