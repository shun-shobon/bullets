// 作成者: j19426 西澤駿太郎
#pragma once

#include "consts.h"
#include "select.h"

typedef struct {
  int age;
  select_t select;
} title_t;

void titleInit(title_t *title);
void titleDrop(title_t *title);
void titleUpdate(title_t *title, phase_t *moveNextPhase);
void titleDraw(const title_t *title);
