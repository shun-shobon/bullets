// 作成者: j19426 西澤駿太郎
#include "opengl.h"

#define WIDTH 600
#define HEIGHT 400

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
  glVertex2f(0.0F, 0.0F);
  glVertex2f(WIDTH, 0.0F);
  glVertex2f(WIDTH, HEIGHT);
  glVertex2f(0.0F, HEIGHT);
  glEnd();

  glutSwapBuffers();
}

void resize(int win_width, int win_height) {
  float aspect = (float)WIDTH / (float)HEIGHT;
  float win_aspect = (float)win_width / (float)win_height;

  // アスペクト比からウィンドウにビューポートを合わせる
  int width;
  int height;
  if (aspect < win_aspect) {
    height = win_height;
    width = (int)((float)win_height * aspect);
  } else {
    width = win_width;
    height = (int)((float)win_width / aspect);
  }

  int x = (win_width - width) / 2;
  int y = (win_height - height) / 2;

  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init() {
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();
  return 0;
}
