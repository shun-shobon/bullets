// 作成者: j19426 西澤駿太郎
#pragma once

#include "vector.h"

struct select_node {
  char *item;
  struct select_node *prev;
  struct select_node *next;
};
typedef struct select_node select_node_t;

typedef struct {
  select_node_t *head;
  select_node_t *tail;
  int len;
  int select;
  int selected;
} select_t;

void selectInit(select_t *select, ...);
void selectDrop(select_t *select);
void selectUpdate(select_t *select);
void selectDraw(const select_t *select, int age, const vec2_t *position,
                float height, float gap);
