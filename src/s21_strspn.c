#include "s21_string.h"

/* Определяет наибольшую длину начального участка строки, на которую указывает
аргумент str_1, содержащего только символы строки, на которую указывает аргумент
str_2. Если первый символ строки str_1 не входит в строку str_2, то возвращаемая
длина – 0. */

s21_size_t s21_strspn(const char *str_1, const char *str_2) {
  s21_size_t i = 0;

  while (str_1[i]) {
    s21_size_t j = 0;
    while (str_2[j]) {
      if (str_1[i] == str_2[j]) break;
      j++;
    }
    if (str_2[j] == '\0') break;
    i++;
  }
  return (i);
}