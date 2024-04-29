#include "s21_string.h"

char *strncat(char *dest, const char *src, s21_size_t n) {
    char *d = dest;
    while (*d != '\0') {
        d++;
    }
    while (n-- != 0 && *src != '\0') {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}
