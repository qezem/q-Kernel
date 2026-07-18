#include "libs/string.h"
#include <stddef.h>

void *memset(void *ptr, int x, size_t n) {
  unsigned char *p = (unsigned char *)ptr;
  unsigned char v = (unsigned char)x;

  for (size_t i = 0; i < n; ++i) {
    p[i] = v;
  }

  return ptr;
}
