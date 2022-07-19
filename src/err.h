// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdbool.h>

typedef enum {
  ERR_FILE_LOAD,  // ファイル読み込みエラー
} errmsg_t;

typedef struct {
  bool has_err;
  errmsg_t errmsg;
  const char *func;
  const char *file;
  int line;
} err_t;

#define INIT_ERR \
  (err_t) { false }

#define setErr(err, msg)      \
  {                           \
    if ((err) != NULL) {      \
      (err)->has_err = true;  \
      (err)->errmsg = msg;    \
      (err)->func = __func__; \
      (err)->file = __FILE__; \
      (err)->line = __LINE__; \
    }                         \
  }

char *strErrmsg(errmsg_t msg);

#define panicIfErr(err) panicIfErr_(__func__, __FILE__, __LINE__, err)
void panicIfErr_(const char *func, const char *file, int line, err_t *err);
