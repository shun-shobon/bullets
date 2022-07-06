// 作成者: j19426 西澤駿太郎
#include "err.h"

#include <stdio.h>
#include <stdlib.h>

char *str_errmsg(errmsg_t msg) {
  switch (msg) {
    case ERR_FILE_LOAD:
      return "ファイルの読み込みに失敗しました";
  }
}

void panic_if_err_(const char *func, const char *file, int line, err_t *err) {
  if (err != NULL && err->has_err) {
    flockfile(stderr);
    fprintf(stderr, "function '%s' panicked at '%s', %s:%d\n", err->func,
            str_errmsg(err->errmsg), err->file, err->line);
    fprintf(stderr, "\tin function '%s' %s:%d\n", func, file, line);
    funlockfile(stderr);
    abort();
  }
}
