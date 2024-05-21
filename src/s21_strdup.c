#include "s21_string.h"

char *s21_strdup(const char *s) {
  char *copy = malloc(s21_strlen(s) + 1);
  if (copy) {
    s21_strcpy(copy, s);
  }
  return copy;
}