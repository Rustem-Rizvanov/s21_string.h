#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) {
    return s21_NULL;
  }

  if (!trim_chars) {
    return (void *)s21_strdup(src);
  }

  char *start = (char *)src;
  char *end = (char *)src + s21_strlen(src) - 1;

  while (*start && s21_strchr(trim_chars, *start)) {
    start++;
  }

  while (end > start && s21_strchr(trim_chars, *end)) {
    end--;
  }

  void *new_str = malloc((end - start + 2) * sizeof(char));
  if (!new_str) {
    return s21_NULL;
  }

  s21_memcpy(new_str, start, end - start + 1);
  ((char *)new_str)[end - start + 1] = '\0';

  return new_str;
}
