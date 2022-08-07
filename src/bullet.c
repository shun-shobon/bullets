// 作成者: j19426 西澤駿太郎
#include "bullet.h"

#include "texture.h"

void bulletDrawA(const bullet_t *bullet) {
  drawTexture(&bullet->position, bullet->size, 1.0F, TEXTURE_BULLET_A);
}

void bulletDrawB(const bullet_t *bullet) {
  drawTexture(&bullet->position, bullet->size, 1.0F, TEXTURE_BULLET_B);
}
