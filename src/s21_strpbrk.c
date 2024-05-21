#include "s21_string.h"

/* Ищет первое вхождение любого символа из строки sym.
Поиск осуществляется в строчке str.
Выводится, на какой позиции находится первый найденный символ из множества. */

char *s21_strpbrk(const char *str, const char *accept) {
  char *result = s21_NULL;

  while (*str && !result) {
    s21_size_t j = 0;
    while (accept[j] != '\0') {
      if (*str == accept[j]) result = (char *)str;
      j++;
    }
    str++;
  }
  return (result);
}
