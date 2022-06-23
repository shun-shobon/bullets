#define GL_SILENCE_DEPRECATION
#include "opengl.h"
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

// clang-format off
static const GLfloat g_vertex_buffer_data[] = {
  -1.0f,-1.0f,-1.0f, // 三角形1:開始
  -1.0f,-1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f, // 三角形1:終了
   1.0f, 1.0f,-1.0f, // 三角形2:開始
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f,-1.0f, // 三角形2:終了
   1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,
   1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f, 1.0f,
   1.0f,-1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f,-1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f,-1.0f,
   1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
   1.0f,-1.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
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
  glClearColor(0.0, 0.0, 0.4, 1.0);

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
