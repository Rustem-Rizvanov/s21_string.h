#include "s21_string.h"

s21_size_t strlen(const char *str) {
    s21_size_t length = 0;
    for (; *(str+length); length++);
    return length;
}