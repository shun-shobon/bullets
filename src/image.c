// 作成者: j19426 西澤駿太郎
#include "image.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "err.h"

void load_bmp(err_t *err, texture_t *texture, char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if (file == NULL) {
    set_err(err, ERR_FILE_LOAD)
    return;
  }

  // ヘッダーサイズ
  static const size_t HEADER_SIZE = 54;
  uint8_t header[HEADER_SIZE];
  // ファイルヘッダーが読み込めるか
  if (fread(header, sizeof(uint8_t), HEADER_SIZE, file) != HEADER_SIZE) {
    fclose(file);
    return;
  }
  // ファイルヘッダーのはじめが"BM"から始まっているか
  if (header[0] != 'B' || header[1] != 'M') {
    fclose(file);
    set_err(err, ERR_FILE_LOAD)
    return;
  }

  // エッダーから各種情報を取得
  texture->width = read_u32_le(header, 0x12);
  texture->height = read_u32_le(header, 0x16);
  // RGB_のため4を掛ける
  uint32_t size = texture->width * texture->height * 4;

  // 画像データの始まりまでシークする
  uint32_t data_offset = read_u32_le(header, 0x0a);
  fseek(file, data_offset, SEEK_SET);
  void *data = malloc_safe(sizeof(uint8_t) * size);

  // 正しく全ピクセルデータが読み込めたか
  if (fread(data, sizeof(uint8_t), size, file) != size) {
    free(data);
    fclose(file);
    set_err(err, ERR_FILE_LOAD)
    return;
  }

  fclose(file);

  // テクスチャ作成
  glGenTextures(1, &texture->id);

  // 作成したテクスチャへバインド
  glBindTexture(GL_TEXTURE_2D, texture->id);

  // OpenGLへ画像を送信
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)texture->width, (GLsizei)texture->height, 0,
               GL_BGRA, GL_UNSIGNED_BYTE, data);
  // 送信したらメモリは開放
  free(data);

  // 拡大縮小の挙動を設定
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
