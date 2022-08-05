// 作成者: j19426 西澤駿太郎
#include "game.h"

#include "consts.h"
#include "enemies.h"
#include "opengl.h"
#include "player.h"
#include "shots.h"

static void gameWindowDraw();

void gameInit(game_state_t *gameState) {
  playerInit(&gameState->player);
  shotsInit(&gameState->shots);
  enemiesInit(&gameState->enemies);
  bulletsInit(&gameState->bullets);
}

void gameUpdate(game_state_t *gameState) {
  playerUpdate(&gameState->player, &gameState->bullets);
  shotsUpdate(&gameState->shots, &gameState->player);
  enemiesUpdate(&gameState->enemies, &gameState->bullets);
  bulletsUpdate(&gameState->bullets);
}

void gameDraw(const game_state_t *gameState) {
  glPushMatrix();
  glTranslatef(GAME_OFFSET.x, GAME_OFFSET.y, 0);
  playerDraw(&gameState->player);
  shotsDraw(&gameState->shots);
  enemiesDraw(&gameState->enemies);
  bulletsDraw(&gameState->bullets);
  glPopMatrix();

  gameWindowDraw();
}

static void gameWindowDraw() {
  glColor3ub(0xff, 0xff, 0xff);
  glBegin(GL_QUAD_STRIP);
  glVertex2f(0.0F, 0.0F);
  glVertex2f(GAME_OFFSET.x, GAME_OFFSET.y);
  glVertex2f(WINDOW_SIZE.x, 0.0F);
  glVertex2f(GAME_OFFSET.x + GAME_SIZE.x, GAME_OFFSET.y);
  glVertex2f(WINDOW_SIZE.x, WINDOW_SIZE.y);
  glVertex2f(GAME_OFFSET.x + GAME_SIZE.x, GAME_OFFSET.y + GAME_SIZE.y);
  glVertex2f(0.0F, WINDOW_SIZE.y);
  glVertex2f(GAME_OFFSET.x, GAME_OFFSET.y + GAME_SIZE.y);
  glVertex2f(0.0F, 0.0F);
  glVertex2f(GAME_OFFSET.x, GAME_OFFSET.y);
  glEnd();
}
