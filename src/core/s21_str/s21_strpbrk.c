#include "../../s21_string.h"


char *strpbrk(const char *s, const char *accept) {
    const char *p = s;
    while (*p != '\0') {
        const char *a = accept;
        while (*a != '\0') {
            if (*p == *a) {
                return (char *)p;
            }
            a++;
        }
        p++;
    }
    return s21_NULL;
}
