#include "s21_string.h"

char *s21_strtok(char *restrict str, const char *restrict sep) {
  static char *p = 0;
  if (str) p = str;
  if (!p) return s21_NULL;

  while (*p && s21_strchr(sep, *p)) {
    p++;
  }
  str = p;

  while (*p && !s21_strchr(sep, *p)) {
    p++;
  }

  if (*p) {
    *p = '\0';
    p++;
  } else if (p == str) {
    return s21_NULL;
  }

  return str;
}
