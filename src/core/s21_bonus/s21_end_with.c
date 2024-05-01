#include "../../s21_string.h"


/* проверяет, оканчивается ли строка src заданной подстрокой totrim, 
 начиная с позиции offset. Вот пошаговое объяснение: */


int endwith(const char *src, const char *totrim, int offset) {
  int res = 0;
  offset--;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[offset] == totrim[i]) res = 1;
  }
  return res;
}