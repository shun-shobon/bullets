// 作成者: j19426 西澤駿太郎
#include "shots.h"

#include "consts.h"
#include "event.h"
#include "player.h"
#include "primitive.h"
#include "texture.h"
#include "vector.h"

static void shotsPushBack(shots_t *shots, shot_t shot);
static void shotDraw(const shot_t *shot);

void shotsInit(shots_t *shots) {
  shots->head = 0;
  shots->tail = 0;
  shots->coolTime = 0;
}

void shotsUpdate(shots_t *shots, const player_t *player, bool isGameOver) {
  shots->coolTime += 1;
  if (!isGameOver && keyState[KEY_Z] && SHOT_INTERVAL < shots->coolTime) {
    shot_t shotCenter =
        shotNew(player->position, (vec2_t){0.0F, SHOT_MOVEMENT});
    shot_t shotRight =
        shotNew(player->position, (vec2_t){SHOT_MOVEMENT * sinf(SHOT_ANGLE),
                                           SHOT_MOVEMENT * cosf(SHOT_ANGLE)});
    shot_t shotLeft =
        shotNew(player->position, (vec2_t){SHOT_MOVEMENT * sinf(-SHOT_ANGLE),
                                           SHOT_MOVEMENT * cosf(-SHOT_ANGLE)});
    shotsPushBack(shots, shotCenter);
    shotsPushBack(shots, shotRight);
    shotsPushBack(shots, shotLeft);
    shots->coolTime = 0;
  }

  int limit = shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
  for (int i = shots->head; i < limit; i++) {
    int idx = i % SHOT_MAX;
    shot_t *shot = &shots->buff[idx];
    shot->position = vec2Add(&shot->position, &shot->velocity);
  }
}

void shotsDraw(const shots_t *shots) {
  int limit = shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
  for (int i = shots->head; i < limit; i++) {
    int idx = i % SHOT_MAX;
    const shot_t *shot = &shots->buff[idx];

    if (shot->wasHit) continue;

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
  drawTexture(&shot->position, SHOT_SIZE * 2, TEXTURE_SHOT);
}
