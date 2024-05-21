#include "s21_string.h"

/* Побайтово проверяет n символов в двух строках и возвращает значение 0,
если строки отличаются, и положительное или отрицательное число, если идентичны.
Если первый отличающийся символ или его код больше, чем у второй строки -
положительное число. Если меньше - отрицательное. */

int s21_strncmp(const char *str_1, const char *str_2, s21_size_t n) {
  //     while (*str_1 == *str_2 && --n && *str_1) {
  //         str_1++, str_2++;
  //     }
  //     return (*str_1 - *str_2);
  // }

  //     while (n > 0 && (*str_1 || *str_2)) {
  //         if (*str_1 != *str_2)
  //             return (*str_1 - *str_2);
  //         str_1++, str_2++, n--;
  //     }
  //     return 0;
  // }

  //     for (s21_size_t i = 0; i < n; i++) {
  //         if (str_1[i] != str_2[i] || str_1[i] == '\0' || str_2[i] == '\0') {
  //             return (int)(str_1[i] - str_2[i]);
  //         }
  //     }
  //     return 0;
  // }

  //     for (s21_size_t i = 0; i < n; i++) {
  //         // Если достигнут конец хотя бы одной строки
  //         if (str_1[i] == '\0' || str_2[i] == '\0') {
  //             return (str_1[i] - str_2[i]);
  //         }
  //         // Сравниваем символы
  //         if (str_1[i] != str_2[i]) {
  //             return (str_1[i] - str_2[i]);
  //         }
  //     }
  //     // Если все символы до n-го равны
  //     return 0;
  // }

  //     for (s21_size_t i = 0; i < n; i++) {
  //         // Если достигнут конец хотя бы одной строки
  //         if (str_1[i] == '\0' || str_2[i] == '\0') {
  //             return (str_1[i] - str_2[i]);
  //         }
  //         // Сравниваем символы
  //         if (str_1[i] != str_2[i]) {
  //             return ((unsigned char)str_1[i] - (unsigned char)str_2[i]);
  //             // Используем приведение к unsigned char для корректного
  //             сравнения
  //         }
  //     }
  //     // Если все символы до n-го равны
  //     return 0;
  // }

  //     // Выделяем память под буферы
  //     char *buffer_1 = (char *)malloc((n + 1) * sizeof(char)); // +1 для
  //     завершающего нуля char *buffer_2 = (char *)malloc((n + 1) *
  //     sizeof(char)); // +1 для завершающего нуля

  //     // Проверяем, удалось ли выделить память
  //     if (buffer_1 == NULL || buffer_2 == NULL) {
  //         // Если выделение не удалось, возвращаем ошибку
  //         // (например, код ошибки -1)
  //         return -1;
  //     }

  //     // Копируем строки в буферы
  //     for (s21_size_t i = 0; i < n; i++) {
  //         buffer_1[i] = str_1[i];
  //         buffer_2[i] = str_2[i];
  //     }
  //     // Завершаем строки нулевыми символами
  //     buffer_1[n] = '\0';
  //     buffer_2[n] = '\0';

  //     // Сравниваем строки с помощью стандартной функции strcmp
  //     int result = s21_strcmp(buffer_1, buffer_2);

  //     // Освобождаем выделенную память
  //     free(buffer_1);
  //     free(buffer_2);

  //     return result;
  // }

  int res = 0;
  for (s21_size_t i = 0; i < n && res == 0; i++) {
    if (((unsigned char *)str_1)[i] != ((unsigned char *)str_2)[i])
      res = ((unsigned char *)str_1)[i] - ((unsigned char *)str_2)[i];
    if (str_1[i] == '\0') i = n;
  }
  return (res);
}