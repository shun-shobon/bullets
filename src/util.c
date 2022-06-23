#include "util.h"

#include "opengl.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void *malloc_safe(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL)
    abort();

  return ptr;
}

char *read_file(const char *filepath) {
  int fd = open(filepath, O_RDONLY);
  if (fd == -1) {
    abort();
  }

  // 通常ファイル出ない場合はエラー
  struct stat stat;
  if (fstat(fd, &stat) != 0 || !S_ISREG(stat.st_mode)) {
    close(fd);
    return NULL;
  }

  size_t size = stat.st_size;

  FILE *fp = fdopen(fd, "r");
  if (fp == NULL) {
    close(fd);
    abort();
  }

  // ファイルサイズ + NULL文字
  char *str = malloc_safe(size + sizeof(char));
  size_t idx = 0;
  char c;
  while ((c = fgetc(fp)) != EOF) {
    str[idx++] = c;
  }
  str[idx] = '\0';

  fclose(fp);

  return str;
}

GLuint create_program(const char *vertex_shader_filepath,
                      const char *fragment_shader_filepath) {
  GLint result;
  GLint log_length;

  // 頂点シェーダのコンパイル
  GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  char *vertex_shader_code = read_file(vertex_shader_filepath);
  glShaderSource(vertex_shader_id, 1, (const char **)&vertex_shader_code, NULL);
  free(vertex_shader_code);
  glCompileShader(vertex_shader_id);
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_length);
    char *vertex_shader_log = malloc_safe(sizeof(char) * log_length);
    glGetShaderInfoLog(vertex_shader_id, log_length, NULL, vertex_shader_log);
    printf("%s", vertex_shader_log);
    free(vertex_shader_log);

    abort();
  }

  // フラグメントシェーダのコンパイル
  GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  char *fragment_shader_code = read_file(fragment_shader_filepath);
  glShaderSource(fragment_shader_id, 1, (const char **)&fragment_shader_code,
                 NULL);
  free(fragment_shader_code);
  glCompileShader(fragment_shader_id);
  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_length);
    char *fragment_shader_log = malloc_safe(sizeof(char) * log_length);
    glGetShaderInfoLog(fragment_shader_id, log_length, NULL,
                       fragment_shader_log);
    printf("%s", fragment_shader_log);
    free(fragment_shader_log);

    abort();
  }

  // プログラムのリンク
  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);
  glGetShaderiv(program_id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
    char *program_log = malloc_safe(sizeof(char) * log_length);
    glGetShaderInfoLog(program_id, log_length, NULL, program_log);
    printf("%s", program_log);
    free(program_log);

    abort();
  }

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  return program_id;
}
