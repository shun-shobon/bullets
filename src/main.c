#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <stdlib.h>

#include "opengl.h"
#include "util.h"

// clang-format off
static const GLfloat g_vertex_buffer_data[] = {
  -1.0F,-1.0F,-1.0F, // 三角形1:開始
  -1.0F,-1.0F, 1.0F,
  -1.0F, 1.0F, 1.0F, // 三角形1:終了
   1.0F, 1.0F,-1.0F, // 三角形2:開始
  -1.0F,-1.0F,-1.0F,
  -1.0F, 1.0F,-1.0F, // 三角形2:終了
   1.0F,-1.0F, 1.0F,
  -1.0F,-1.0F,-1.0F,
   1.0F,-1.0F,-1.0F,
   1.0F, 1.0F,-1.0F,
   1.0F,-1.0F,-1.0F,
  -1.0F,-1.0F,-1.0F,
  -1.0F,-1.0F,-1.0F,
  -1.0F, 1.0F, 1.0F,
  -1.0F, 1.0F,-1.0F,
   1.0F,-1.0F, 1.0F,
  -1.0F,-1.0F, 1.0F,
  -1.0F,-1.0F,-1.0F,
  -1.0F, 1.0F, 1.0F,
  -1.0F,-1.0F, 1.0F,
   1.0F,-1.0F, 1.0F,
   1.0F, 1.0F, 1.0F,
   1.0F,-1.0F,-1.0F,
   1.0F, 1.0F,-1.0F,
   1.0F,-1.0F,-1.0F,
   1.0F, 1.0F, 1.0F,
   1.0F,-1.0F, 1.0F,
   1.0F, 1.0F, 1.0F,
   1.0F, 1.0F,-1.0F,
  -1.0F, 1.0F,-1.0F,
   1.0F, 1.0F, 1.0F,
  -1.0F, 1.0F,-1.0F,
  -1.0F, 1.0F, 1.0F,
   1.0F, 1.0F, 1.0F,
  -1.0F, 1.0F, 1.0F,
   1.0F,-1.0F, 1.0F
};

static const GLfloat g_color_buffer_data[] = {
    0.583F,  0.771F,  0.014F,
    0.609F,  0.115F,  0.436F,
    0.327F,  0.483F,  0.844F,
    0.822F,  0.569F,  0.201F,
    0.435F,  0.602F,  0.223F,
    0.310F,  0.747F,  0.185F,
    0.597F,  0.770F,  0.761F,
    0.559F,  0.436F,  0.730F,
    0.359F,  0.583F,  0.152F,
    0.483F,  0.596F,  0.789F,
    0.559F,  0.861F,  0.639F,
    0.195F,  0.548F,  0.859F,
    0.014F,  0.184F,  0.576F,
    0.771F,  0.328F,  0.970F,
    0.406F,  0.615F,  0.116F,
    0.676F,  0.977F,  0.133F,
    0.971F,  0.572F,  0.833F,
    0.140F,  0.616F,  0.489F,
    0.997F,  0.513F,  0.064F,
    0.945F,  0.719F,  0.592F,
    0.543F,  0.021F,  0.978F,
    0.279F,  0.317F,  0.505F,
    0.167F,  0.620F,  0.077F,
    0.347F,  0.857F,  0.137F,
    0.055F,  0.953F,  0.042F,
    0.714F,  0.505F,  0.345F,
    0.783F,  0.290F,  0.734F,
    0.722F,  0.645F,  0.174F,
    0.302F,  0.455F,  0.848F,
    0.225F,  0.587F,  0.040F,
    0.517F,  0.713F,  0.338F,
    0.053F,  0.959F,  0.120F,
    0.393F,  0.621F,  0.362F,
    0.673F,  0.211F,  0.457F,
    0.820F,  0.883F,  0.371F,
    0.982F,  0.099F,  0.879F
};
// clang-format on

static GLuint program_id;
static GLuint vertexbuffer;
static GLuint colorbuffer;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(program_id);

  GLuint vertexAttributeLocation = glGetAttribLocation(program_id, "position");
  GLuint colorAttributeLocation = glGetAttribLocation(program_id, "color");

  glEnableVertexAttribArray(vertexAttributeLocation);
  glEnableVertexAttribArray(colorAttributeLocation);

  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(vertexAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0,
                        NULL);

  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glVertexAttribPointer(colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

  glPushMatrix();
  glTranslated(-2, 2, 0);
  glRotated(90, 0, 1, 0);
  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
  glPopMatrix();

  glDisableVertexAttribArray(vertexAttributeLocation);
  glDisableVertexAttribArray(colorAttributeLocation);

  glutSwapBuffers();
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.0, 3.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void init() {
  glClearColor(0.0F, 0.0F, 0.4F, 1.0F);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  program_id =
      create_program("./shaders/vertex.glsl", "./shaders/fragment.glsl");

  // バッファのバインド
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
               g_color_buffer_data, GL_STATIC_DRAW);
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
