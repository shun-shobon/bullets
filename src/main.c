#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>

#include "util.h"

// clang-format off
GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 1.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { 0.0, 1.0, 1.0 },
};

int edge[][2] = {
  { 0, 1 },
  { 1, 2 },
  { 2, 3 },
  { 3, 0 },
  { 4, 5 },
  { 5, 6 },
  { 6, 7 },
  { 7, 4 },
  { 0, 4 },
  { 1, 5 },
  { 2, 6 },
  { 3, 7 },
};

int face[][4] = {
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 },
};

GLdouble color[][3] = {
  { 1.0, 0.0, 0.0 }, /* 赤 */
  { 0.0, 1.0, 0.0 }, /* 緑 */
  { 0.0, 0.0, 1.0 }, /* 青 */
  { 1.0, 1.0, 0.0 }, /* 黄 */
  { 1.0, 0.0, 1.0 }, /* マゼンタ */
  { 0.0, 1.0, 1.0 }, /* シアン */
};

GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};
// clang-format on

GLfloat light0pos[] = {0.0, 3.0, 5.0, 1.0};
GLfloat light1pos[] = {5.0, 3.0, 0.0, 1.0};

GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat red[] = {0.8, 0.2, 0.2, 1.0};

void cube(void) {
  glBegin(GL_QUADS);
  for (int i = 0; i < 6; i++) {
    glNormal3dv(normal[i]);
    // glColor3dv(color[i]);
    for (int j = 0; j < 4; j++) {
      glVertex3dv(vertex[face[i][j]]);
    }
  }
  glEnd();
}

void idle(void) { glutPostRedisplay(); }

void display(void) {
  static int r = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light0pos);

  glPushMatrix();

  glRotated((double)r, 0.0, 1.0, 0.0);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

  cube();

  glPushMatrix();
  glTranslated(1.0, 1.0, 1.0);
  glRotated((double)(r * 2), 0.0, 1.0, 0.0);
  cube();
  glPopMatrix();

  glPopMatrix();

  glutSwapBuffers();

  if (++r >= 360)
    r = 0;
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (GLdouble)w / (GLdouble)h, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, UNUSED int x, UNUSED int y) {

  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      glutIdleFunc(idle);
    } else {
      glutIdleFunc(NULL);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) {
      glutPostRedisplay();
    }
    break;
  }
}

void keyboard(unsigned char key, UNUSED int x, UNUSED int y) {
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':
    exit(0);
  }
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
  glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(300, 300);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);

  init();
  glutMainLoop();
  return 0;
}
