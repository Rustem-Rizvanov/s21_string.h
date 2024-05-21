#include "s21_string.h"

char* s21_strcat(char* destination, const char* source) {
  char* ptr = destination + s21_strlen(destination);

  while (*source != '\0') {
    *ptr++ = *source++;
  }

  *ptr = '\0';

  return destination;
}