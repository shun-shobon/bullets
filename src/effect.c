// 作成者: j19426 西澤駿太郎
#include "effect.h"

#include <math.h>

#include "opengl.h"

static const int GRID_GAP = 60;

void gridDraw(const vec2_t *position, const vec2_t *size, int age) {
  float startMargin = (float)(age % GRID_GAP);

  glLineWidth(1.0F);
  glColor3ub(0xff, 0xff, 0xff);

  glBegin(GL_LINES);

  int columnCount = (int)ceilf(size->x / (float)GRID_GAP);
  for (int i = 0; i < columnCount; i++) {
    float x = (float)(i * GRID_GAP) + startMargin + position->x;
    glVertex2f(x, position->y);
    glVertex2f(x, position->y + size->y);
  }

  int rowCount = (int)ceilf(size->y / (float)GRID_GAP);
  for (int i = 0; i < rowCount; i++) {
    float y = (float)(i * GRID_GAP) + startMargin + position->y;
    glVertex2f(position->x, y);
    glVertex2f(position->x + size->x, y);
  }

  glEnd();
}
