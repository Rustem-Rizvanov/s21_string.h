#include "../../s21_string.h"


/* Ищет позицию последнего вхождения символа c в строке str. */


char *strrchr(const char *s, int c) {
    const char *p = s;
    const char *last = s21_NULL;
    while (*p != '\0') {
        if (*p == (char)c) {
            last = p;
        }
        p++;
    }
    if (*p == (char)c) {
        return (char *)p;
    }
    return (char *)last;
}
