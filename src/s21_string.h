#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <ctype.h>
#include <limits.h>  // Для определения краевых значений
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>  // s21_strspn
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_sscanf.h"  //Nealpadm bonus lib

#define s21_NULL ((void *)0)
typedef long unsigned int s21_size_t;

// Tarramad Sprintf function
typedef struct variables {
  int width;
  int precision;
  int format_adress;
  int str_adress;
  int length;
  int zero_flag;
  int plus_flag;
  int is_negative;
  int l_flag;
  int h_flag;
  int minus_flag;
  int space_flag;
  int point_flag;
  int no_precision;
  char flag;
} variables;

int s21_sprintf(char *str, const char *format, ...);
int char_to_digit(char c);
int end_of_parce(char c, int *space_count, variables *var);
void percent_parser(const char *format, variables *var);
void default_settings(char *string, variables *var);
void float_to_ascii(double number, variables *var, char *float_point);
void h_flag_parcer(const char *format, variables *var);
void increase_format_adress(char const *format, variables *var);
void l_flag_parcer(const char *format, variables *var);
void l_h_flags_process(char *str, variables *var, long int number);
void minus_flag_parcer(const char *format, variables *var);
void number_to_str(char *string, long long unsigned int n, variables *var,
                   int *i);
void plus_flag_parcer(const char *format, variables *var);
void point_parcer(const char *format, variables *var);
void precision_parcer(const char *format, variables *var);
void print_float_to_string(char *str, variables *var, double number);
void print_int_to_str(char *str, variables *var, long int number);
void print_unsigned_to_str(char *str, variables *var, long unsigned int number);
void print_str_to_str(char *str, variables *var, char *string);
void restore_variables(variables *var);
void slash_parcer(char *str, char const *format, variables *var);
void space_flag_parcer(const char *format, variables *var);
void width_parcer(const char *format, variables *var);
void width_setup(char *str, variables *var);
void zero_flag_parcer(const char *format, variables *var);
void ud_precision(char *integer, variables *var);
void plus_minus_space(char *string, variables *var, int *i);
void print_char_to_string(char *str, variables *var, char c);
void round_float(char *float_point, int i);
void print_empty(char *str, variables *var);
void big_double(double number, char *float_point, int *i);
void after_point_to_ascii(double after_point, variables *var, char *float_point,
                          int *i);
void place_point_in_place(char *float_point, int point_position, int *i,
                          variables *var);
char *create_a_demonic_bottom();

// Armondvi functions
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, size_t start_index);

// Nealpadm functions
typedef struct Holder {
  int code;
  struct Holder *next;
} Holder;

void init(Holder **holderPointer);
void push(Holder **holderPointer, int data);
int pop(Holder **holderPointer);
int peek(Holder **holderPointer);
int isAny(Holder *holderPointer, int value);
void destroy(Holder **holderPointer);

char *s21_strdup(const char *s);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
int s21_sscanf(const char *str, const char *format, ...);
long int s21_strtol(const char **str, Holder **holderPointer, int radix);
long double s21_strtold(const char **str, Holder **holderPointer);
int getArg(const char **str, va_list *argp, int type, int mod,
           Holder **holderPointer, char *strMem);
int getCharacter(const char **str, va_list *argp, Holder **holderPointer);
int getString(const char **str, va_list *argp, Holder **holderPointer);
int getInteger(const char **str, va_list *argp, Holder **holderPointer, int mod,
               int radix);
int getDouble(const char **str, va_list *argp, Holder **holderPointer, int mod);
int getPointer(const char **str, va_list *argp, Holder **holderPointer);
int getNothing(const char **str, va_list *argp, Holder **holderPointer,
               const char *strMem);
int getPercent(const char **str, Holder **holderPointer);
int getWidth(Holder **holderPointer);
char *getFirstDigit(const char *str);
int getAsterisk(Holder **holderPointer);
int s21_atoi(char **str);
int specifierReader(char **pfl, int *mod);
int formatLineReader(char **pfl);

#endif  // SRC_S21_STRING_H_
