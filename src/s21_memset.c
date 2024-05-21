#include "s21_string.h"

/* Заполняет первые size байт массива символом, указанным в symbol.*/

void *s21_memset(void *str, int c, s21_size_t size) {
  unsigned char *p = (unsigned char *)str;
  if (p) {
    while (size--) {
      *p++ = (unsigned char)c;
    }
  }
  return str;
}