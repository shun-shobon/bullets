#pragma once

#include <stdbool.h>

// 誤差
#define EPSILON 0.000001F

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

vec2_t vec2Add(const vec2_t *v1, const vec2_t *v2);
vec2_t vec2Sub(const vec2_t *v1, const vec2_t *v2);
vec2_t vec2Mul(const vec2_t *v1, const vec2_t *v2);
vec2_t vec2Div(const vec2_t *v1, const vec2_t *v2);
vec2_t vec2MulScalar(const vec2_t *v, float s);
vec2_t vec2DivScalar(const vec2_t *v, float s);
float vec2Dot(const vec2_t *v1, const vec2_t *v2);
float vec2Cross(const vec2_t *v1, const vec2_t *v2);
float vec2Length(const vec2_t *v);
float vec2LengthSq(const vec2_t *v);
float distancePointPoint(const vec2_t *p1, const vec2_t *p2);
float distancePointSegment(const vec2_t *p1, const vec2_t *p2,
                           const vec2_t *v2);
float distanceSegmentSegment(const vec2_t *p1, const vec2_t *v1,
                             const vec2_t *p2, const vec2_t *v2);
bool isSharpAngle(const vec2_t *p1, const vec2_t *p2, const vec2_t *p3);
bool isCrossSegmentSegment(const vec2_t *p1, const vec2_t *v1, const vec2_t *p2,
                           const vec2_t *v2);
