#include "vector.h"

#include <math.h>
#include <stdbool.h>

vec2_t vec2Add(vec2_t *v1, vec2_t *v2) {
  return (vec2_t){v1->x + v2->x, v1->y + v2->y};
}

vec2_t vec2Sub(vec2_t *v1, vec2_t *v2) {
  return (vec2_t){v1->x - v2->x, v1->y - v2->y};
}

vec2_t vec2Mul(vec2_t *v1, vec2_t *v2) {
  return (vec2_t){v1->x * v2->x, v1->y * v2->y};
}

vec2_t vec2Div(vec2_t *v1, vec2_t *v2) {
  return (vec2_t){v1->x / v2->x, v1->y / v2->y};
}

vec2_t vec2MulScalar(vec2_t *v, float s) {
  return (vec2_t){v->x * s, v->y * s};
}

vec2_t vec2DivScalar(vec2_t *v, float s) {
  return (vec2_t){v->x / s, v->y / s};
}

float vec2Dot(vec2_t *v1, vec2_t *v2) { return v1->x * v2->x + v1->y * v2->y; }

float vec2Cross(vec2_t *v1, vec2_t *v2) {
  return v1->x * v2->y - v1->y * v2->x;
}

float vec2Length(vec2_t *v) { return sqrtf(vec2LengthSq(v)); }

float vec2LengthSq(vec2_t *v) { return v->x * v->x + v->y * v->y; }

vec2_t vec2_normalize(vec2_t *v) {
  float length = vec2Length(v);
  return vec2DivScalar(v, length);
}

bool vec2_is_vertical(vec2_t *v1, vec2_t *v2) {
  // 内積が0ならば垂直関係
  float dot = vec2Dot(v1, v2);
  return -EPSILON < dot && dot < EPSILON;
}

bool vec2_is_parallel(vec2_t *v1, vec2_t *v2) {
  // 外積が0ならば並行関係
  float cross = vec2Cross(v1, v2);
  return -EPSILON < cross && cross < EPSILON;
}

bool vec2_is_sharp_angle(vec2_t *v1, vec2_t *v2) {
  // 内積が正なら鋭角
  float dot = vec2Dot(v1, v2);
  return 0.0F < dot;
}
