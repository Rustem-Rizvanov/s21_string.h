#include "s21_string.h"

// margarme

char *s21_strrchr(const char *s, int c) {
  const char *p = s21_NULL;

  for (;;) {
    if (*s == (char)c) p = s;
    if (*s++ == '\0') return (char *)p;
  }
}
