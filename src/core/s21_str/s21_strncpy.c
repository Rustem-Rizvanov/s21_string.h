#include "../../s21_string.h"



char *strncpy(char *dest, const char *src, s21_size_t n) {
    char *d = dest;
    while (n-- != 0 && *src != '\0') {
        *d++ = *src++;
    }
    while (n-- != 0) {
        *d++ = '\0';
    }
    return dest;
}
