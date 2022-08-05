// 作成者: j19426 西澤駿太郎
#include "primitive.h"

#include <math.h>
#include <stdbool.h>

#include "opengl.h"
#include "vector.h"

void drawCircle(const vec2_t *center, float radius, bool fill) {
  static int COUNT = 20;

  if (fill) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center->x, center->y);
  }
  for (int i = 0; i <= COUNT; i++) {
    float theta = 2.0F * (float)M_PI * (float)i / (float)COUNT;
    glVertex2f(center->x + radius * sinf(theta),
               center->y - radius * cosf(theta));
  }
  glEnd();
}
