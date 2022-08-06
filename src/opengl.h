// 作成者: j19426 西澤駿太郎
#pragma once

#ifdef __linux__  // Linuxの場合
#include <GL/glut.h>
#include <glpng.h>

#elif __MACH__  // macOSの場合
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <glpng.h>

#elif __CYGWIN__  // Cygwinの場合
#include <GL/glut.h>
#include <glpng.h>

#else  // それ以外の場合はエラー
#error Unsupported platform.

#endif
