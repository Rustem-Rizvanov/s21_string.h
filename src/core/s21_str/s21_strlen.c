#include "../../s21_string.h"


/* Длина строки. 
Вычисляет количество символов в строке до её конца. 
Конец строки не входит в подсчёт символов. */


s21_size_t strlen(const char *str) {
    s21_size_t length = 0;
    while (str && *str != '\0') {
        length++;
        str++;
    }
    return length;
}
