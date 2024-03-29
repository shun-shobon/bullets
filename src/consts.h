// 作成者: j19426 西澤駿太郎
#pragma once

#include <math.h>

#include "vector.h"

#define PI 3.14159265358979F

// フェイズ
typedef enum {
  PHASE_NONE,
  PHASE_TITLE,
  PHASE_GAME,
} phase_t;

// 画面サイズ
static const vec2_t WINDOW_SIZE = {340, 480};

// ゲームサイズとオフセット
static const vec2_t GAME_SIZE = {300, 400};
static const vec2_t GAME_OFFSET = {20, 60};

// プレイヤー関連
static const float PLAYER_MOVEMENT = 6.0F;
static const float PLAYER_SIZE = 3.0F;
// 自弾
static const float SHOT_MOVEMENT = 10.0F;
static const float SHOT_ANGLE = 8.0F * 2.0F * PI / 360.0F;
static const int SHOT_INTERVAL = 5;
static const float SHOT_SIZE = 5.0F;

// 敵スポーン関連
static const int SPAWN_INTERVAL_MIN = 20;
static const int SPAWN_INTERVAL_MAX = 300;
