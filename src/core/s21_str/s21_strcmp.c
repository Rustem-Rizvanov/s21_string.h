#include "s21_string.h"

int strcmp(char *str1, char *str2) {
    for (;*str1 && *str1 == *str2; str1++, str2++);
    return *str1 - *str2;
}