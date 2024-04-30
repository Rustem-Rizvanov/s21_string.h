#include "../../s21_string.h"


/* Выполняет поиск первого вхождения в первую строку любого из символов второй строки, 
и возвращает количество символов до найденного первого вхождения. */


s21_size_t s21_strcspn(const char *str, const char *reject) {
   s21_size_t initial_length = 0;

   s21_size_t len1 = s21_strlen(str);

   s21_size_t len2 = s21_strlen(reject);

   for (s21_size_t i = 0; i < len1; i++) {
    bool found_match = false;
        for (s21_size_t j = 0; j < len2; j++) {
            if (reject[i] == str[i]) {
                found_match = true;
                break;
            }

            if (!found_match) break; // nt found
            else initial_length++;
        }
   }

   return initial_length;
}
