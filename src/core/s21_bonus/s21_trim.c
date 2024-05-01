#include "../../s21_string.h"


/* Возвращает новую строку, в которой из первоначальной строки 
удаляются все начальные и конечные вхождения набора заданных символов. 
В случае какой-либо ошибки следует вернуть значение NULL */


void *s21_trim(const char *src, const char *trim_chars) {
    char *string = s21_NULL;
    if (!trim_chars || s21_strlen(trim_chars) == 0)
        trim_chars = " \f\n\r\t\v";
    if (src && trim_chars) {
        char *first_string = (char *)src;
        char *last_string = (char *)src + s21_strlen(src);
        for ( ; *first_string && s21_strchr(trim_chars,
        *first_string); first_string++) {
        }
        for ( ; last_string != first_string &&
        s21_strchr(trim_chars, * (last_string - 1)); last_string--) {
        }
        string = calloc((last_string - first_string + 1), sizeof(char));
        if (string) {
        s21_strncpy(string, first_string, last_string - first_string);
        *(string + (last_string - first_string)) = '\0';
        }
    }
    return string;
}