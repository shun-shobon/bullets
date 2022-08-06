// 作成者: j19426 西澤駿太郎
#pragma once

#include "consts.h"

typedef struct {
  int age;
} title_t;

void titleInit(title_t *title);
void titleDrop(title_t *title);
void titleUpdate(title_t *title, phase_t *moveNextPhase);
void titleDraw(const title_t *title);
