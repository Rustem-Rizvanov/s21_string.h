#include "s21_string.h"

/* Копирует sze символов из строки src в строку dest.
Если значение n больше строки, то остальное пространство заполнится нулевыми
символами. */

char *s21_strncpy(char *dest, const char *src, s21_size_t size) {
  //     s21_size_t i;
  //     for (i = 0; i < size && src[i] != '\0'; i++) {
  //         dest[i] = src[i];
  //     for (; i < size; i++)
  //         dest[i] = 0;
  // }
  // return dest;
  // }

  s21_memset(dest, '\0', size);

  for (s21_size_t i = 0; i < size && src[i]; i++) {
    dest[i] = src[i];
  }

  return dest;
}