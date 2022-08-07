// 作成者: j19426 西澤駿太郎
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "consts.h"
#include "enemies.h"
#include "event.h"
#include "opengl.h"
#include "player.h"
#include "primitive.h"
#include "shots.h"
#include "stats.h"
#include "text.h"
#include "texture.h"

static void gameWindowDraw();
static void gameScoreDraw(const stats_t *stats);
static void gameLevelDraw(const stats_t *stats);
static void gameOverDraw(const game_t *game);

void gameInit(game_t *game) {
  srandom(time(NULL));

  game->isGameOver = false;
  statsInit(&game->stats);
  playerInit(&game->player);
  shotsInit(&game->shots);
  enemiesInit(&game->enemies);
  bulletsInit(&game->bullets);
  spawnerInit(&game->spawner, &game->stats);
}

void gameDrop(game_t *game) { enemiesDrop(&game->enemies); }

void gameUpdate(game_t *game, phase_t *moveNextPhase) {
  statsUpdate(&game->stats);
  playerUpdate(&game->player, &game->bullets, &game->isGameOver);
  shotsUpdate(&game->shots, &game->player, game->isGameOver);
  enemiesUpdate(&game->enemies, &game->bullets, &game->shots, &game->player,
                &game->stats);
  bulletsUpdate(&game->bullets);
  spawnerUpdate(&game->spawner, &game->enemies, &game->stats, game->isGameOver);

  if (game->isGameOver && keyState[KEY_X]) *moveNextPhase = PHASE_TITLE;
}

void gameDraw(const game_t *game) {
  glPushMatrix();
  glTranslatef(GAME_OFFSET.x, GAME_OFFSET.y, 0);
  playerDraw(&game->player, game->isGameOver);
  shotsDraw(&game->shots);
  enemiesDraw(&game->enemies);
  bulletsDraw(&game->bullets);
  glPopMatrix();

  gameWindowDraw();
  gameScoreDraw(&game->stats);
  gameLevelDraw(&game->stats);
  gameOverDraw(game);
}

static void gameWindowDraw() {
  glColor3ub(0x00, 0x00, 0x20);
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

static void gameScoreDraw(const stats_t *stats) {
  char scoreStr[32];
  snprintf(scoreStr, 32, "SCORE %09d", stats->score);

  vec2_t position = {GAME_OFFSET.x, GAME_OFFSET.y - 20.0F};
  drawText(&position, scoreStr, 20.0F, 1.0F, ALIGN_LEFT);
}

static void gameLevelDraw(const stats_t *stats) {
  char scoreStr[16];
  snprintf(scoreStr, 16, "LEVEL %02d", stats->level);

  vec2_t position = {GAME_OFFSET.x, GAME_OFFSET.y - 40.0F};
  drawText(&position, scoreStr, 20.0F, 1.0F, ALIGN_LEFT);
}

static void gameOverDraw(const game_t *game) {
  if (!game->isGameOver) return;

  drawTexture(&(vec2_t){WINDOW_SIZE.x / 2.0F, WINDOW_SIZE.y * 0.7F},
              GAME_SIZE.x, TEXTURE_GAMEOVER);
  drawText(
      &(vec2_t){WINDOW_SIZE.x / 2.0F, WINDOW_SIZE.y * 0.3F},
      "PRESS X TO MOVE TITLE", 13.0F,
      0.5F + sinf((float)game->stats.age * 2.0F * (float)M_PI / 40.0F) / 2.0F,
      ALIGN_CENTER);
}
