#include "util.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "opengl.h"

void *mallocSafe(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) abort();

  return ptr;
}

uint32_t readU32Le(const uint8_t *array, size_t offset) {
  return array[offset + 3] << 3 | array[offset + 2] << 2 |
         array[offset + 1] << 1 | array[offset];
}

char *readFile(const char *filepath) {
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
  char *str = mallocSafe(size + sizeof(char));
  size_t idx = 0;
  char c;
  while ((c = (char)fgetc(fp)) != EOF) {
    str[idx++] = c;
  }
  str[idx] = '\0';

  fclose(fp);

  return str;
}

GLuint createProgram(const char *vertex_shader_filepath,
                     const char *fragment_shader_filepath) {
  GLint result;
  GLint logLength;

  // 頂点シェーダのコンパイル
  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  char *vertexShaderCode = readFile(vertex_shader_filepath);
  glShaderSource(vertexShaderId, 1, (const char **)&vertexShaderCode, NULL);
  free(vertexShaderCode);
  glCompileShader(vertexShaderId);
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &logLength);
    char *vertexShaderLog = mallocSafe(sizeof(char) * logLength);
    glGetShaderInfoLog(vertexShaderId, logLength, NULL, vertexShaderLog);
    printf("%s", vertexShaderLog);
    free(vertexShaderLog);

    abort();
  }

  // フラグメントシェーダのコンパイル
  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  char *fragmentShaderCode = readFile(fragment_shader_filepath);
  glShaderSource(fragmentShaderId, 1, (const char **)&fragmentShaderCode, NULL);
  free(fragmentShaderCode);
  glCompileShader(fragmentShaderId);
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &logLength);
    char *fragmentShaderLog = mallocSafe(sizeof(char) * logLength);
    glGetShaderInfoLog(fragmentShaderId, logLength, NULL, fragmentShaderLog);
    printf("%s", fragmentShaderLog);
    free(fragmentShaderLog);

    abort();
  }

  // プログラムのリンク
  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  glGetShaderiv(programId, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &logLength);
    char *programLog = mallocSafe(sizeof(char) * logLength);
    glGetShaderInfoLog(programId, logLength, NULL, programLog);
    printf("%s", programLog);
    free(programLog);

    abort();
  }

  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);

  return programId;
}
