#pragma once

// 誤差
#define EPSILON 0.000001f

// 二次元ベクトル
typedef struct {
  float x;
  float y;
} vec2_t;

// 線分
typedef struct {
  vec2_t point;
  vec2_t vector;
} seg2_t;

// 円
typedef struct {
  vec2_t point;
  float radius;
} circle2_t;

// カプセル
typedef struct {
  seg2_t segment;
  float radius;
} capsule2_t;

vec2_t vec2Add(vec2_t *v1, vec2_t *v2);
vec2_t vec2Sub(vec2_t *v1, vec2_t *v2);
vec2_t vec2Mul(vec2_t *v1, vec2_t *v2);
vec2_t vec2Div(vec2_t *v1, vec2_t *v2);
vec2_t vec2MulScalar(vec2_t *v, float s);
vec2_t vec2DivScalar(vec2_t *v, float s);
float vec2Dot(vec2_t *v1, vec2_t *v2);
float vec2Cross(vec2_t *v1, vec2_t *v2);
float vec2Length(vec2_t *v);
float vec2LengthSq(vec2_t *v);
