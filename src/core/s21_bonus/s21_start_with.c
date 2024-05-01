#include "../../s21_string.h"


/* проверяет, начинается ли строка src с подстроки totrim, 
 начиная с указанного смещения offset. Вот объяснение: */


int startwith(const char *src, const char *totrim, int offset) {
  int res = 0;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[offset] == totrim[i]) res = 1;
  }
  return res;
}