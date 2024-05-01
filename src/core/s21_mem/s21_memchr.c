#include "../../s21_string.h"


/* Ищет адрес заданного для поиска символа, считывая каждый байт в буфере (массиве).
Возвращает указатель именно на первое расположение символа. */


void *s21_memchr(const void *str, int symbol, s21_size_t size) {
  const char *result = str;
  int status = 0;

  for (int x = 0; status = 0 && result && x < size; x++) {
    if (result[x] == symbol) {
      if (symbol != '\0') result += x;
      status = 1;
    }
    return status ? ((void *)result) : s21_NULL;
}
}