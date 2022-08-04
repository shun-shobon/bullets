// 作成者: j19426 西澤駿太郎
#include "shots.h"

#include "event.h"
#include "opengl.h"
#include "player.h"
#include "vector.h"

static void shotsPushBack(shots_t *shots, shot_t shot);

void shotsInit(shots_t *shots) {
  shots->head = 0;
  shots->tail = 0;
}

void shotsUpdate(shots_t *shots, int timeDelta, const player_t *player) {
  static const vec2_t SHOT_VECTOR = {0.0F, 0.2F};
  static const int shotInterval = 100;

  static int shotCoolTime = 0;
  shotCoolTime += timeDelta;
  if (keyState[KEY_Z] && shotInterval < shotCoolTime) {
    shot_t shot = {
        .position = player->position, .vector = SHOT_VECTOR, .didHit = false};
    shotsPushBack(shots, shot);
    shotCoolTime = 0;
  }

  int limit = shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
  for (int i = shots->head; i < limit; i++) {
    int idx = i % SHOT_MAX;
    shot_t *shot = &shots->buff[idx];
    vec2_t incremental = vec2MulScalar(&shot->vector, (float)timeDelta);
    shot->position = vec2Add(&shot->position, &incremental);
  }
}

void shotsDraw(const shots_t *shots) {
  glPointSize(5.0F);
  glColor3ub(0x55, 0xaa, 0x55);
  glBegin(GL_POINTS);

  int limit = shots->head <= shots->tail ? shots->tail : shots->tail + SHOT_MAX;
  for (int i = shots->head; i < limit; i++) {
    int idx = i % SHOT_MAX;
    const shot_t *shot = &shots->buff[idx];

    glVertex2f(shot->position.x, shot->position.y);
  }

  glEnd();
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
