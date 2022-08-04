// 作成者: j19426 西澤駿太郎
#include "bullets.h"

static void bulletsPushBack(bullets_t *bullets, bullet_t bullet);
static void bulletsGC(bullets_t *bullets);

void bulletsInit(bullets_t *bullets) {
  bullets->head = 0;
  bullets->tail = 0;
}

void bulletsUpdate(bullets_t *bullets, int timeDelta) {
  int limit = bullets->head <= bullets->tail ? bullets->tail
                                             : bullets->tail + BULLETS_MAX;
  for (int i = bullets->head; i < limit; i++) {
    int idx = i % BULLETS_MAX;
    bullet_t *bullet = &bullets->buff[idx];
    vec2_t incremental = vec2MulScalar(&bullet->vector, (float)timeDelta);
    bullet->position = vec2Add(&bullet->position, &incremental);
  }

  bulletsGC(bullets);
}

void bulletsDraw(const bullets_t *bullets) {
  int limit = bullets->head <= bullets->tail ? bullets->tail
                                             : bullets->tail + BULLETS_MAX;
  for (int i = bullets->head; i < limit; i++) {
    int idx = i % BULLETS_MAX;
    const bullet_t *bullet = &bullets->buff[idx];
    bullet->draw(bullet);
  }
}

static void bulletsPushBack(bullets_t *bullets, bullet_t bullet) {
  bullets->buff[bullets->tail] = bullet;
  bullets->tail += 1;
  if (BULLETS_MAX <= bullets->tail) {
    bullets->tail = 0;
  }

  if (bullets->head == bullets->tail) {
    bullets->head += 1;
    if (BULLETS_MAX <= bullets->head) {
      bullets->head = 0;
    }
  }
}

static void bulletsGC(bullets_t *bullets) {
  int limit = bullets->head <= bullets->tail ? bullets->tail
                                             : bullets->tail + BULLETS_MAX;
  for (int i = bullets->head; i < limit; i++) {
    int idx = i % BULLETS_MAX;
    bullet_t *bullet = &bullets->buff[idx];

    if (bullet->age < BULLETS_MAX_AGE) break;

    bullets->head += 1;
    if (BULLETS_MAX <= bullets->head) {
      bullets->head = 0;
    }
  }
}
