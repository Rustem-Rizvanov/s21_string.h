#include "s21_string.h"

void *s21_to_lower(const char *str) {
  void *lower = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t str_length = 0;
    while (str[str_length] != '\0') {
      str_length++;
    }
    lower = malloc((str_length + 1) * sizeof(char));
    if (lower != s21_NULL) {
      for (s21_size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90) {
          ((char *)lower)[i] = str[i] + 32;
        } else {
          ((char *)lower)[i] = str[i];
        }
      }
      ((char *)lower)[str_length] = '\0';
    }
  }
  return lower;
}
