// 作成者: j19426 西澤駿太郎
#pragma once

#include "vector.h"

// 画面サイズ
static const vec2_t WINDOW_SIZE = {600, 400};

// ゲームサイズとオフセット
static const vec2_t GAME_SIZE = {300, 360};
static const vec2_t GAME_OFFSET = {20, 20};

// プレイヤー関連
static const float PLAYER_MOVEMENT = 3.0F;
static const float PLAYER_SIZE = 3.0F;
// 自弾
static const float SHOT_MOVEMENT = 10.0F;
static const float SHOT_SIZE = 5.0F;

// 敵スポーン関連
static const int SPAWN_INTERVAL_MIN = 20;
static const int SPAWN_INTERVAL_MAX = 300;
