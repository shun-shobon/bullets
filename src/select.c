// 作成者: j19426 西澤駿太郎
#include "select.h"

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "event.h"
#include "primitive.h"
#include "text.h"
#include "texture.h"
#include "util.h"
#include "vector.h"

static void selectPushBack(select_t *select, char *option);

void selectInit(select_t *select, ...) {
  select->head = NULL;
  select->tail = NULL;
  select->len = 0;
  select->select = 0;
  select->selected = -1;

  va_list ap;
  va_start(ap, select);
  char *option;
  while ((option = va_arg(ap, char *))) {
    selectPushBack(select, option);
  }
  va_end(ap);
}

void selectDrop(select_t *select) {
  select_node_t *node = select->head;
  while (node) {
    select_node_t *next = node->next;
    free(node);
    node = next;
  }
}

void selectUpdate(select_t *select) {
  if (isKeyClick(KEY_UP)) {
    select->select -= 1;
    if (select->select < 0) select->select = select->len - 1;
  }
  if (isKeyClick(KEY_DOWN)) {
    select->select += 1;
    if (select->len <= select->select) select->select = 0;
  }
  if (isKeyClick(KEY_Z)) {
    select->selected = select->select;
  }
}

void selectDraw(const select_t *select, int age, const vec2_t *position,
                float height, float gap) {
  float totalHeight = (float)select->len * (height + gap) - gap;

  vec2_t textPosition = {position->x,
                         position->y + totalHeight / 2.0F - height / 2.0F};
  int i = 0;
  for (select_node_t *node = select->head; node; node = node->next) {
    float width =
        drawText(&textPosition, node->item, height, 1.0F, ALIGN_CENTER);

    if (select->select == i) {
      vec2_t cursorPosition = {textPosition.x - width / 2.0F - gap,
                               textPosition.y};
      float alpha = 0.5F + sinf((float)age * 2.0F * (float)M_PI / 20.0F) / 2.0F;
      drawTexture(&cursorPosition, height, alpha, TEXTURE_CURSOR);
    }

    textPosition.y -= height + gap;
    i += 1;
  }
}

static void selectPushBack(select_t *select, char *option) {
  select_node_t *node = mallocSafe(sizeof(select_node_t));
  node->item = option;
  node->prev = select->tail;
  node->next = NULL;

  if (select->tail) {
    select->tail->next = node;
  } else {
    select->head = node;
  }

  select->tail = node;
  select->len += 1;
}
