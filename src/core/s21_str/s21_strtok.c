#include "../../s21_string.h"


/* Разбивает строку str на части по указанному в delim разделителе. 
Это может быть любой символ, который не будет печататься с остальными строками. */



char *s21_strtok(char *str, const char *delim) {
    static char *next_token = s21_NULL;
    if (str != s21_NULL) {
        next_token = str;
    } else if (next_token == s21_NULL) {
        return s21_NULL;
    }
    char *start = next_token;
    next_token += s21_strspn(next_token, delim);
    if (*next_token == '\0') {
        next_token = s21_NULL;
        return s21_NULL;
    }
    char *end = next_token + s21_strcspn(next_token, delim);
    if (*end != '\0') {
        *end = '\0';
        next_token = end + 1;
    } else {
        next_token = s21_NULL;
    }
    return start;
}
