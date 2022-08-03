// 作成者: j19426 西澤駿太郎
#pragma once

#include <stdlib.h>

void deltaTimeUpdate(int *timeDelta, int *fps);
void fpsDraw(int fps);

void *malloc_safe(size_t size);
