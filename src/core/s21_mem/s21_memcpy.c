#include "../s21_string.h"

/* Копирует байты из src в dest, то есть между буферами.
Размер буфера назначения (куда копируется) должен быть таким же или больше. */


void *s21_memcpy(void *dest, const void *src, s21_size_t size) {
  if (dest == NULL) return NULL;

  char *char_dest = (char *) dest;
  char *char_src = (char *) src;

  for (int i = 0; i < size; i++) {
    char_dest[i] = char_src[i];

    return dest;  
  }
}