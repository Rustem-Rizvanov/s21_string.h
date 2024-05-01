#include "../../s21_string.h"


/* Ищет позицию первого вхождения символа в указанной строке. */


char *s21_strchr(const char *str, int symbol) {
    while (*str != '\0') {
        if (*str == symbol) return (char *) str;
        str++;
    }
    return s21_NULL;
}
