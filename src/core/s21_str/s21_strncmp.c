#include "../../s21_string.h"


/* Побайтово проверяет n символов в двух строках и возвращает значение 0,
если строки отличаются, и положительное или отрицательное число, если идентичны. 
Если первый отличающийся символ или его код больше, чем у второй строки - положительное число.
Если меньше - отрицательное. */


int s21_strncmp(const char *str_1, const char *str_2, s21_size_t n) {
    while (*str_1 == *str_2 && --n && *str_1) {
        str_1++, str_2++;
    }
    return (*str_1 - *str_2); 
}