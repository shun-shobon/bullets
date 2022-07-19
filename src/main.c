// 作成者: j19426 西澤駿太郎
#include <stdio.h>

#include "consts.h"
#include "event.h"
#include "game.h"
#include "opengl.h"
#include "player.h"

void idle() {
  static int time_before = 0;
  static int before_print_fps = 0;
  static int frame_count = 0;
  int time_now = glutGet(GLUT_ELAPSED_TIME);
  int time_delta = time_now - time_before;
  time_before = time_now;

  frame_count++;
  if (time_now - before_print_fps > 1000) {
    printf("fps: %d\n", frame_count);
    before_print_fps = time_now;
    frame_count = 0;
  }

  player_update(time_delta);

  glutPostRedisplay();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(0x00, 0x00, 0x30);
  glBegin(GL_QUADS);
  glVertex2f(0.0F, 0.0F);
  glVertex2f(WINDOW_SIZE.x, 0.0F);
  glVertex2f(WINDOW_SIZE.x, WINDOW_SIZE.y);
  glVertex2f(0.0F, WINDOW_SIZE.y);
  glEnd();

  game_draw();

  glutSwapBuffers();
}

void resize(int win_width, int win_height) {
  float aspect = WINDOW_SIZE.x / WINDOW_SIZE.y;
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
  gluOrtho2D(0.0F, WINDOW_SIZE.x, 0.0F, WINDOW_SIZE.y);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init() {
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  for (int i = 0; i < KEY_LENGTH; i++) {
    key_state[i] = false;
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(idle);
  glutSpecialFunc(handle_special_key_down);
  glutSpecialUpFunc(handle_special_key_up);

  init();
  glutMainLoop();
  return 0;
}
