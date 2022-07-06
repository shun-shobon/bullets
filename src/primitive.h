#pragma once

// 誤差
#define EPSILON 0.000001f

// 二次元ベクトル
typedef struct {
  float x;
  float y;
} vec2;

// 線分
typedef struct {
  vec2 point;
  vec2 vector;
} seg2;

// 円
typedef struct {
  vec2 point;
  float radius;
} circle2;

// カプセル
typedef struct {
  seg2 segment;
  float radius;
} capsule2;

vec2 vec2_add(vec2 *v1, vec2 *v2);
vec2 vec2_sub(vec2 *v1, vec2 *v2);
vec2 vec2_mul(vec2 *v1, vec2 *v2);
vec2 vec2_div(vec2 *v1, vec2 *v2);
vec2 vec2_mul_scalar(vec2 *v, float s);
vec2 vec2_div_scalar(vec2 *v, float s);
float vec2_dot(vec2 *v1, vec2 *v2);
float vec2_cross(vec2 *v1, vec2 *v2);
float vec2_length(vec2 *v);
float vec2_length_sq(vec2 *v);
