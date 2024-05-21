#include "s21_string.h"

/* Копирует байты из src в dest, то есть между буферами.
В отличии от memcpy массивы могут пересекаться между собою.
Размер буфера назначения (куда копируется) должен быть таким же или больше. */

void *s21_memmove(void *dest, const void *src, s21_size_t size) {
  if (src < dest) {
    while (size-- > 0)
      *((unsigned char *)dest + size) = *((unsigned char *)src + size);
  } else if (src > dest) {
    for (s21_size_t i = 0; i < size; i++)
      *((unsigned char *)dest + i) = *((unsigned char *)src + i);
  }
  return dest;
}
