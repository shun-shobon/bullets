// 作成者: j19426 西澤駿太郎
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "consts.h"
#include "enemies.h"
#include "gamestate.h"
#include "opengl.h"
#include "player.h"
#include "shots.h"
#include "text.h"

static void gameWindowDraw();
static void gameScoreDraw(const gamestate_t *gamestate);
static void gameLevelDraw(const gamestate_t *gamestate);

void gameInit(game_t *game) {
  srandom(time(NULL));

  gamestateInit(&game->gamestate);
  playerInit(&game->player);
  shotsInit(&game->shots);
  enemiesInit(&game->enemies);
  bulletsInit(&game->bullets);
  spawnerInit(&game->spawner, &game->gamestate);
}

void gameDrop(game_t *game) { enemiesDrop(&game->enemies); }

void gameUpdate(game_t *game, __attribute__((unused)) phase_t *moveNextPhase) {
  gamestateUpdate(&game->gamestate);
  playerUpdate(&game->player, &game->bullets);
  shotsUpdate(&game->shots, &game->player);
  enemiesUpdate(&game->enemies, &game->bullets, &game->shots, &game->player,
                &game->gamestate);
  bulletsUpdate(&game->bullets);
  spawnerUpdate(&game->spawner, &game->enemies, &game->gamestate);
}

void gameDraw(const game_t *game) {
  glPushMatrix();
  glTranslatef(GAME_OFFSET.x, GAME_OFFSET.y, 0);
  playerDraw(&game->player);
  shotsDraw(&game->shots);
  enemiesDraw(&game->enemies);
  bulletsDraw(&game->bullets);
  glPopMatrix();

  gameWindowDraw();
  gameScoreDraw(&game->gamestate);
  gameLevelDraw(&game->gamestate);
}

static void gameWindowDraw() {
  glColor3ub(0x00, 0x00, 0x40);
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

  glLineWidth(1.0F);
  glColor3ub(0xff, 0xff, 0xff);
  glBegin(GL_LINE_LOOP);
  glVertex2f(GAME_OFFSET.x, GAME_OFFSET.y);
  glVertex2f(GAME_OFFSET.x + GAME_SIZE.x, GAME_OFFSET.y);
  glVertex2f(GAME_OFFSET.x + GAME_SIZE.x, GAME_OFFSET.y + GAME_SIZE.y);
  glVertex2f(GAME_OFFSET.x, GAME_OFFSET.y + GAME_SIZE.y);
  glEnd();
}

static void gameScoreDraw(const gamestate_t *gamestate) {
  char scoreStr[32];
  snprintf(scoreStr, 32, "SCORE %09d", gamestate->score);

  vec2_t position = {GAME_OFFSET.x, GAME_OFFSET.y - 20.0F};
  drawText(&position, scoreStr, 20.0F, 1.0F, ALIGN_LEFT);
}

static void gameLevelDraw(const gamestate_t *gamestate) {
  char scoreStr[16];
  snprintf(scoreStr, 16, "LEVEL %02d", gamestate->level);

  vec2_t position = {GAME_OFFSET.x, GAME_OFFSET.y - 40.0F};
  drawText(&position, scoreStr, 20.0F, 1.0F, ALIGN_LEFT);
}
