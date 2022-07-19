// 作成者: j19426 西澤駿太郎
#include "game.h"

#include "consts.h"
#include "opengl.h"
#include "player.h"

void game_draw() {
  glPushMatrix();
  glTranslatef(GAME_OFFSET.x, GAME_OFFSET.y, 0);
  player_draw();
  glPopMatrix();

  // 枠を描画
  glColor3ub(0xFF, 0xFF, 0xFF);
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
