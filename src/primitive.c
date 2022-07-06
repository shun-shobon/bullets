#include "primitive.h"

#include <math.h>
#include <stdbool.h>

vec2 vec2_add(vec2 *v1, vec2 *v2) {
  return (vec2){v1->x + v2->x, v1->y + v2->y};
}

vec2 vec2_sub(vec2 *v1, vec2 *v2) {
  return (vec2){v1->x - v2->x, v1->y - v2->y};
}

vec2 vec2_mul(vec2 *v1, vec2 *v2) {
  return (vec2){v1->x * v2->x, v1->y * v2->y};
}

vec2 vec2_div(vec2 *v1, vec2 *v2) {
  return (vec2){v1->x / v2->x, v1->y / v2->y};
}

vec2 vec2_mul_scalar(vec2 *v, float s) { return (vec2){v->x * s, v->y * s}; }

vec2 vec2_div_scalar(vec2 *v, float s) { return (vec2){v->x / s, v->y / s}; }

float vec2_dot(vec2 *v1, vec2 *v2) { return v1->x * v2->x + v1->y * v2->y; }

float vec2_cross(vec2 *v1, vec2 *v2) { return v1->x * v2->y - v1->y * v2->x; }

float vec2_length(vec2 *v) { return sqrtf(vec2_length_sq(v)); }

float vec2_length_sq(vec2 *v) { return v->x * v->x + v->y * v->y; }

vec2 vec2_normalize(vec2 *v) {
  float length = vec2_length(v);
  return vec2_div_scalar(v, length);
}

bool vec2_is_vertical(vec2 *v1, vec2 *v2) {
  // 内積が0ならば垂直関係
  float dot = vec2_dot(v1, v2);
  return -EPSILON < dot && dot < EPSILON;
}

bool vec2_is_parallel(vec2 *v1, vec2 *v2) {
  // 外積が0ならば並行関係
  float cross = vec2_cross(v1, v2);
  return -EPSILON < cross && cross < EPSILON;
}

bool vec2_is_sharp_angle(vec2 *v1, vec2 *v2) {
  // 内積が正なら鋭角
  float dot = vec2_dot(v1, v2);
  return 0.0F < dot;
}
