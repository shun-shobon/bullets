#include "vector.h"

#include <math.h>
#include <stdbool.h>

#include "util.h"

vec2_t vec2Add(const vec2_t *v1, const vec2_t *v2) {
  return (vec2_t){v1->x + v2->x, v1->y + v2->y};
}

vec2_t vec2Sub(const vec2_t *v1, const vec2_t *v2) {
  return (vec2_t){v1->x - v2->x, v1->y - v2->y};
}

vec2_t vec2Mul(const vec2_t *v1, const vec2_t *v2) {
  return (vec2_t){v1->x * v2->x, v1->y * v2->y};
}

vec2_t vec2Div(const vec2_t *v1, const vec2_t *v2) {
  return (vec2_t){v1->x / v2->x, v1->y / v2->y};
}

vec2_t vec2MulScalar(const vec2_t *v, float s) {
  return (vec2_t){v->x * s, v->y * s};
}

vec2_t vec2DivScalar(const vec2_t *v, float s) {
  return (vec2_t){v->x / s, v->y / s};
}

float vec2Dot(const vec2_t *v1, const vec2_t *v2) {
  return v1->x * v2->x + v1->y * v2->y;
}

float vec2Cross(const vec2_t *v1, const vec2_t *v2) {
  return v1->x * v2->y - v1->y * v2->x;
}

float vec2Length(const vec2_t *v) { return sqrtf(vec2LengthSq(v)); }

float vec2LengthSq(const vec2_t *v) { return v->x * v->x + v->y * v->y; }

float distancePointPoint(const vec2_t *p1, const vec2_t *p2) {
  vec2_t v = vec2Sub(p1, p2);
  return vec2Length(&v);
}

float distancePointSegment(const vec2_t *p1, const vec2_t *p2,
                           const vec2_t *v2) {
  vec2_t v2End = vec2Add(p2, v2);

  if (!isSharpAngle(p1, p2, &v2End)) {
    return distancePointPoint(p1, p2);
  }
  if (!isSharpAngle(p1, &v2End, p2)) {
    return distancePointPoint(p1, &v2End);
  }

  vec2_t p12 = vec2Sub(p2, p1);
  return absf(vec2Cross(v2, &p12)) / vec2Length(v2);
}

float distanceSegmentSegment(const vec2_t *p1, const vec2_t *v1,
                             const vec2_t *p2, const vec2_t *v2) {
  float v1LenSq = vec2LengthSq(v1);
  float v2LenSq = vec2LengthSq(v2);

  // どちらの線分も縮退
  if (v1LenSq < EPSILON && v2LenSq < EPSILON) {
    return distancePointPoint(p1, p2);
  }
  // 1つ目の線分が縮退
  if (v1LenSq < EPSILON && !(v2LenSq < EPSILON)) {
    return distancePointSegment(p1, p2, v2);
  }
  // 2つ目の線分が縮退
  if (!(v1LenSq < EPSILON) && v2LenSq < EPSILON) {
    return distancePointSegment(p2, p1, v1);
  }
  // 線分が交差
  if (isCrossSegmentSegment(p1, v1, p2, v2)) {
    return 0.0F;
  }

  vec2_t v1End = vec2Add(p1, v1);
  vec2_t v2End = vec2Add(p2, v2);

  float len[4];
  len[0] = distancePointSegment(p1, p2, v2);
  len[1] = distancePointSegment(&v1End, p2, v2);
  len[2] = distancePointSegment(p2, p1, v1);
  len[3] = distancePointSegment(&v2End, p1, v1);
  float min = HUGE_VALF;
  for (int i = 0; i < 4; i++) {
    if (len[i] < min) {
      min = len[i];
    }
  }

  return min;
}

bool isSharpAngle(const vec2_t *p1, const vec2_t *p2, const vec2_t *p3) {
  vec2_t v21 = vec2Sub(p1, p2);
  vec2_t v23 = vec2Sub(p3, p2);

  return 0.0F <= vec2Dot(&v21, &v23);
}

bool isCrossSegmentSegment(const vec2_t *p1, const vec2_t *v1, const vec2_t *p2,
                           const vec2_t *v2) {
  vec2_t v1End = vec2Add(p1, v1);
  vec2_t v2End = vec2Add(p2, v2);

  vec2_t v12 = vec2Sub(p2, p1);
  vec2_t v12End = vec2Sub(&v2End, p1);
  vec2_t v21 = vec2Sub(p1, p2);
  vec2_t v21End = vec2Sub(&v1End, p2);

  return vec2Cross(v1, &v12) * vec2Cross(v1, &v12End) < 0.0F &&
         vec2Cross(v2, &v21) * vec2Cross(v2, &v21End) < 0.0F;
}

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
