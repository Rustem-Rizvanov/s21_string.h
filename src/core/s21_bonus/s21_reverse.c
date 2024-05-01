#include "../../s21_string.h"


/* переворачивает строку str на месте (без создания новой строки) 
 и возвращает указатель на неё. Вот как это работает: */


char *s21_reverse(char *str) {
  int lenStr = s21_strlen(str);
  for (int x = 0; x < (lenStr / 2); x += 1) {
    char aux = str[lenStr - 1 - x];
    str[lenStr - 1 - x] = str[x];
    str[x] = aux;
  }
  return str;
}