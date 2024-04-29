#include "../../s21_string.h"

s21_size_t strcspn(const char *s, const char *reject) {
    const char *p = s;
    while (*p != '\0') {
        const char *r = reject;
        while (*r != '\0') {
            if (*p == *r) {
                return p - s;
            }
            r++;
        }
        p++;
    }
    return p - s;
}
