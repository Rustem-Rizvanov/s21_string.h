#include "s21_string.h"

void *s21_to_upper(const char *str) {
  void *upper = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t str_length = 0;
    while (str[str_length] != '\0') {
      str_length++;
    }
    upper = malloc((str_length + 1) * sizeof(char));
    if (upper != s21_NULL) {
      for (s21_size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
          ((char *)upper)[i] = str[i] - 32;
        } else {
          ((char *)upper)[i] = str[i];
        }
      }
      ((char *)upper)[str_length] = '\0';
    }
  }
  return upper;
}
