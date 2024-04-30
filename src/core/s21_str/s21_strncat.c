#include "../../s21_string.h"


/* Добавляет в строку, на которую указывает аргумент dest, 
строку, на которую указывает аргумент src, пока не встретится символ конца строки 
или пока не будет добавлено size символов. */

char *s21_strncat(char *dest, const char *src, s21_size_t size) {
    char *x;
    x = dest;
    while (*dest)
        dest++;
    while (*src && size--)
        *dest++ = *src++;
    *dest = 0;
    return x;
}