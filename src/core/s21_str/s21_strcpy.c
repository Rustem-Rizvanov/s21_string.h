#include "../../s21_string.h"

/* Копирует одну строку в другую. */

char* s21_strcpy(char* dest, const char* src) {
    s21_size_t i = 0;
    while (src[i]){
        dest[i] = src[i];

        i++;
    }
    dest[i] = '\0';
    return dest;
}

