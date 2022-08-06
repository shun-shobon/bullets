// 作成者: j19426 西澤駿太郎
#include <stdlib.h>

#include "consts.h"
#include "effect.h"
#include "event.h"
#include "global.h"
#include "opengl.h"
#include "text.h"
#include "texture.h"

#define UPDATE_INTERVAL 30

global_t global;

void idle() { glutPostRedisplay(); }

void update(__attribute__((unused)) int value) {
  globalUpdate(&global);

  if (keyState[KEY_Q]) {
    exit(0);
  }

  glutTimerFunc(UPDATE_INTERVAL, update, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(0x00, 0x00, 0x50);
  glBegin(GL_QUADS);
  glVertex2f(0.0F, 0.0F);
  glVertex2f(WINDOW_SIZE.x, 0.0F);
  glVertex2f(WINDOW_SIZE.x, WINDOW_SIZE.y);
  glVertex2f(0.0F, WINDOW_SIZE.y);
  glEnd();

  globalDraw(&global);

  glutSwapBuffers();
}

void resize(int winWidth, int winHeight) {
  float aspect = WINDOW_SIZE.x / WINDOW_SIZE.y;
  float winAspect = (float)winWidth / (float)winHeight;

  // アスペクト比からウィンドウにビューポートを合わせる
  int width;
  int height;
  if (aspect < winAspect) {
    height = winHeight;
    width = (int)((float)winHeight * aspect);
  } else {
    width = winWidth;
    height = (int)((float)winWidth / aspect);
  }

  int x = (winWidth - width) / 2;
  int y = (winHeight - height) / 2;

  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0F, WINDOW_SIZE.x, 0.0F, WINDOW_SIZE.y);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init() {
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  textureInit();
  textInit();
  eventInit();
  globalInit(&global);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  // イベントハンドラの登録
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(idle);
  glutTimerFunc(UPDATE_INTERVAL, update, 0);
  glutKeyboardFunc(handleKeyDown);
  glutKeyboardUpFunc(handleKeyUp);
  glutSpecialFunc(handleSpecialKeyDown);
  glutSpecialUpFunc(handleSpecialKeyUp);

  init();
  glutMainLoop();
  return 0;
}
