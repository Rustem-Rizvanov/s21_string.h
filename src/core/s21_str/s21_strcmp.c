#include "../../s21_string.h"


/* Сравнивает две строки и возвращает 0, если строки индентичны,
и положительное или отрицательное число, если строки разные
(взависимости от того, больше или меньше строка другой). */


int s21_strcmp(const char *str_1, const char *str_2) {
int result = 0;

for (s21_size_t i = 0; (str_1[i] || str_2[i]) && result == 0; i++) {
  if (((unsigned char *)str_1)[i] != ((unsigned char *)str_2)[i]) 
    result = ((unsigned char *)str_1)[i] - ((unsigned char *) str_2)[i];
}
return result;
}

  // while (*str_1 == *str_2 && str_1) {
  //   str_1++, str_2++;
  // }
  // return (*str_1 - *str_2);

