#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  char *tmpstr1 = (char *)str;

  for (; *tmpstr1 != '\0'; tmpstr1++) {
    if (*tmpstr1 == c) {
      return tmpstr1;
    }
  }
  if (c == '\0') {
    return tmpstr1;
  }

  return s21_NULL;
}
