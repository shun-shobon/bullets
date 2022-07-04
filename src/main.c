// 作成者: j19426 西澤駿太郎
#include <stdio.h>

#include "image.h"
#include "opengl.h"
#include "util.h"

static const GLfloat vertex_buffer_data[][3] = {
    {0.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 1.0F},
    {1.0F, 0.0F, 1.0F}, {0.0F, 0.0F, 1.0F}, {0.0F, 0.0F, 0.0F},
};

static const GLfloat uv_buffer_data[][2] = {{0.0F, 0.0F}, {1.0F, 0.0F},
                                            {1.0F, 1.0F}, {1.0F, 1.0F},
                                            {0.0F, 1.0F}, {0.0F, 0.0F}};

static GLuint program_id;
static GLuint vertex_buffer;
static GLuint uv_buffer;
static texture_t texture;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(program_id);

  GLuint position_attribute = glGetAttribLocation(program_id, "attr_position");
  GLuint uv_attribute = glGetAttribLocation(program_id, "attr_uv");
  GLint texture_sampler_uniform =
      glGetUniformLocation(program_id, "unif_texture");

  glEnableVertexAttribArray(position_attribute);
  glEnableVertexAttribArray(uv_attribute);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.id);
  glUniform1i(texture_sampler_uniform, 0);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
  glVertexAttribPointer(uv_attribute, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

  glDisableVertexAttribArray(position_attribute);
  glDisableVertexAttribArray(uv_attribute);

  glutSwapBuffers();
}

void resize(int width, int height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 0.1, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.0, 3.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void init() {
  glClearColor(0.0F, 0.0F, 0.4F, 1.0F);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // シェーダの読み込み
  program_id = create_program("shaders/vertex.glsl", "shaders/fragment.glsl");

  // テクスチャの読み込み
  err_t err = load_bmp("assets/debug.bmp", &texture);
  if (err != ERR_NO) {
    abort();
  }

  // バッファのバインド
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data,
               GL_STATIC_DRAW);

  glGenBuffers(1, &uv_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data,
               GL_STATIC_DRAW);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(300, 300);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();
  return 0;
}
