#include "../../s21_string.h"


/* Возвращает копию строки (str), преобразованной в верхний регистр. 
В случае какой-либо ошибки возвращает значение NULL. */


void *s21_to_upper(const char *str) {
    char *string = s21_NULL;
    if (str != s21_NULL) {
        s21_size_t n = s21_strlen(str);
        string = calloc(n + 1, sizeof(char));
        if (string) {
            for (s21_size_t i = 0; i < n ; i++) {
                if (str[i] >= 'a' && str[i] <= 'z')
                    string[i] = str[i] - 32;
                else
                    string[i] = str[i];
            }
            string[n] ='\0';
        }
    }
    return string;
}