// 作成者: j19426 西澤駿太郎
#pragma once

typedef struct {
  int age;
} title_t;

void titleInit(title_t *title);
void titleUpdate(title_t *title);
void titleDraw(const title_t *title);
