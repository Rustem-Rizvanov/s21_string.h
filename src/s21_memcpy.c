#include "s21_string.h"

/* Копирует байты из src в dest, то есть между буферами.
Размер буфера назначения (куда копируется) должен быть таким же или больше. */

void *s21_memcpy(void *dest, const void *src, s21_size_t size) {
  if (dest == s21_NULL) return s21_NULL;

  unsigned char *char_dest = (unsigned char *)dest;
  unsigned char *char_src = (unsigned char *)src;

  for (s21_size_t i = 0; i < size; i++) {
    char_dest[i] = char_src[i];
  }
  return dest;
}
