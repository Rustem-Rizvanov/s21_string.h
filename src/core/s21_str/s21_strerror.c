#include "../../s21_string.h"


/* Формирует отчёт об ошибке в определённой строке. */


char *strerror(int errnum) {
    static char error_message[101];
    s21_memset(error_message, 0, 101);
    if (errnum < 0 || errnum > MAX) {
#ifndef __APPLE__
            s21_sprintf(error_message, "Unknown error: %d", errnum);
#elif defined __linux__ 
            s21_sprintf(error_message, "No error information");
#endif
    } else {
        static char *arr[] = error;
        s21_memcpy(error_message, arr[errnum], s21_strlen(arr[errnum]));
    }
    return error_message;
}