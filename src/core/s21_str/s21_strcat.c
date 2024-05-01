#include "../../s21_string.h"

/* Объединяет указанные в буффере строки в одну,
все строки будут записаны в первый указанный аргумент, её и надо выводить в sprintf. */


char *s21_strcat(char *dest, const char *scr) {
    s21_size_t i = 0, j = 0;
    char *first = dest;
    const char *second = scr;
    while (first[i] != '\0') {
      i++;
    }
    while (second[j] != '\0') {
      first[i] = second[j];
      i++;
      j++;
  }
  first[i] = '\0';
  return first;
}