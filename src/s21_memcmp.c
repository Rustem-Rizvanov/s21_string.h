#include "s21_string.h"

/* Побайтно сравнивает два массива, на которые указывают аргументы.
Сравнение продолжается, пока массив не закончится или пока не будет найдено
различие. */

int s21_memcmp(const void *mem_1, const void *mem_2, s21_size_t size) {
  //     unsigned char *str_1 = (unsigned char *)mem_1;
  //     unsigned char *str_2 = (unsigned char *)mem_2;
  //     int result = 0;

  //     for (int x = 0; result == 0 && str_1[x] != '\0' && x < size; x += 1)
  //      result = str_1[x] - str_2[x];

  //      return result;
  // }
  unsigned char *s1 = (unsigned char *)mem_1;
  unsigned char *s2 = (unsigned char *)mem_2;
  int dif = 0;
  for (s21_size_t i = 0; i < size; i++) {
    dif = *s1 - *s2;
    if (*s1 != *s2) break;
    s1++;
    s2++;
  }
  return dif;
}