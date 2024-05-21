#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i, j;
  i = 0;
  int flag = 0;

  while (*(str1 + i) && !flag) {
    j = 0;
    while (*(str2 + j) && !flag) {
      if (*(str1 + i) == *(str2 + j)) {
        flag = 1;
      }
      if (!flag) j++;
    }
    if (!*(str2 + j) && !flag) {
      i++;
    }
  }
  return i;
}