// 作成者: j19426 西澤駿太郎
#pragma once

// Linuxの場合
#ifdef __linux__
#include <GL/glut.h>

// macOSの場合
#elif __MACH__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

// Cygwinの場合
#elif __CYGWIN__
#include <GL/glut.h>

// それ以外の場合はエラー
#else
#error Unsupported platform.

#endif
