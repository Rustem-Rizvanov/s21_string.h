#include "s21_string.h"

/* ищет первое вхождение строки, на которую указывает аргумент haystack,
в строку , на которую указывает аргумент needle.
Если строка haystack имеет нулевую длину, то функция вернет указатель на начало
строки needle. */

char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }
  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;
    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }
    if (*n == '\0') {
      return (char *)haystack;
    }
    haystack++;
  }
  return s21_NULL;
}
