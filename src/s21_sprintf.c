#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  variables var = {0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  while (format[var.format_adress] != '\0') {
    if (format[var.format_adress] == '\\') {
      slash_parcer(str, format, &var);
    }
    if (format[var.format_adress] == '%') {
      increase_format_adress(format, &var);
      if (var.format_adress < (int)s21_strlen(format)) {
        percent_parser(format, &var);
      }
    }
    if (var.flag == 'd') {
      long int d = va_arg(args, long int);
      if (var.no_precision && d == 0) {
        print_empty(str, &var);
      } else {
        l_h_flags_process(str, &var, d);
      }
    } else if (var.flag == 'c') {
      char c = va_arg(args, int);
      print_char_to_string(str, &var, c);
    } else if (var.flag == 'f') {
      print_float_to_string(str, &var, va_arg(args, double));
    } else if (var.flag == 's') {
      print_str_to_str(str, &var, va_arg(args, char *));
    } else if (var.flag == 'u') {
      long int u = va_arg(args, long int);
      if (var.no_precision && u == 0) {
        print_empty(str, &var);
      } else {
        l_h_flags_process(str, &var, u);
      }
    } else if (var.flag == '%') {
      str[var.str_adress] = '%';
      var.str_adress++;
    } else {
      str[var.str_adress] = format[var.format_adress];
      var.str_adress++;
    }
    restore_variables(&var);
    increase_format_adress(format, &var);
  }
  str[var.str_adress] = '\0';
  return var.str_adress;
}

void l_h_flags_process(char *str, variables *var, long int number) {
  if (var->flag != 'u') {
    if (var->l_flag) {
      print_int_to_str(str, var, number);
    } else if (var->h_flag) {
      print_int_to_str(str, var, (short int)number);
    } else {
      print_int_to_str(str, var, (int)number);
    }
  } else {
    if (var->l_flag) {
      print_unsigned_to_str(str, var, (unsigned long int)number);
    } else if (var->h_flag) {
      print_unsigned_to_str(str, var, (unsigned short int)number);
    } else {
      print_unsigned_to_str(str, var, (unsigned int)number);
    }
  }
}

void print_float_to_string(char *str, variables *var, double number) {
  if (var->precision == -1) {
    var->precision = 6;
  }
  if (number < 0) {
    number *= -1;
    var->is_negative = 1;
  }
  char *float_point = create_a_demonic_bottom();
  float_to_ascii(number, var, float_point);
  var->length = (int)s21_strlen(float_point);
  if (var->zero_flag && var->width > var->length) {
    for (int i = 0; i < var->length; i++) {
      if (float_point[i] == '+' || float_point[i] == '-') {
        float_point[i] = '0';
      }
    }
  }
  print_str_to_str(str, var, float_point);
  free(float_point);
}

void float_to_ascii(double number, variables *var, char *float_point) {
  int i = 0;
  int point_position = 0;
  double after_point = 0;
  int end = 1;
  if (number < 0) {
    number *= -1;
    var->is_negative = 1;
  }
  if (number > 9325781235683690496.0) {
    if (var->is_negative || var->plus_flag || var->space_flag) {
      end--;
    }
    plus_minus_space(float_point, var, &i);
    big_double(number, float_point, &i);
    point_position = i;
    after_point = 0;
  } else {
    long long unsigned int before_point = (long long unsigned int)number;
    after_point = number - before_point;
    number_to_str(float_point, before_point, var, &i);
    point_position = i;
  }
  after_point_to_ascii(after_point, var, float_point, &i);
  place_point_in_place(float_point, point_position, &i, var);
  round_float(float_point, i);
  float_point[s21_strlen(float_point) - end] = '\0';
}

void round_float(char *float_point, int i) {
  int carry = 0;
  int shift = 0;
  if (float_point[i - 1] > '4') {
    carry = 1;
  }
  int k = i - 2;
  while (carry > 0 && k >= 0) {
    if (float_point[k] != '-' && float_point[k] != '+') {
      if (float_point[k] == '.') {
        k--;
      }
      if (float_point[k] != '9') {
        float_point[k]++;
        carry = 0;
      } else {
        float_point[k] = '0';
      }
    }
    k--;
  }
  if (float_point[0] != '-' || float_point[0] != '+') {
    shift = 1;
  }
  if (carry == 1) {
    for (int j = s21_strlen(float_point); j >= shift; j--) {
      float_point[j + 1] = float_point[j];
    }
    float_point[0 + shift] = '1';
  }
}

void print_int_to_str(char *str, variables *var, long int number) {
  if (number == LONG_MIN) {
    char long_min[100] = "-9223372036854775808";
    var->length = (int)s21_strlen(long_min);
    print_str_to_str(str, var, long_min);
  } else {
    char num[100] = {'\0'};
    if (number < 0 && number != LONG_MIN) {
      number *= -1;
      var->is_negative = 1;
    }
    int i = 0;
    number_to_str(num, number, var, &i);
    var->length = (int)s21_strlen(num);
    print_str_to_str(str, var, num);
  }
}
void print_unsigned_to_str(char *str, variables *var,
                           long unsigned int number) {
  if (number == ULONG_MAX) {
    char num[100] = "18446744073709551615";
    var->length = (int)s21_strlen(num);
    print_str_to_str(str, var, num);
  } else {
    char num[100] = {'\0'};
    int i = 0;
    number_to_str(num, number, var, &i);
    var->length = (int)s21_strlen(num);
    print_str_to_str(str, var, num);
  }
}

void number_to_str(char *integer, long long unsigned int n, variables *var,
                   int *i) {
  long long unsigned int integer_int = n;
  *i = 0;
  plus_minus_space(integer, var, i);
  char *integer_revert = create_a_demonic_bottom();
  int j = 0;
  if (integer_int == 0) {
    integer_revert[j++] = '0';
  }
  while (integer_int > 0) {
    integer_revert[j++] = (integer_int % 10) + '0';
    integer_int /= 10;
  }
  for (int k = 0; k < j / 2; k++) {
    char temp = integer_revert[k];
    integer_revert[k] = integer_revert[j - k - 1];
    integer_revert[j - k - 1] = temp;
  }
  for (int k = 0; k < (int)s21_strlen(integer_revert); k++) {
    integer[(*i)++] = integer_revert[k];
  }
  ud_precision(integer, var);
  free(integer_revert);
}

void ud_precision(char *integer, variables *var) {
  var->length = (int)s21_strlen(integer);
  if (var->space_flag || var->is_negative || var->plus_flag) {
    var->length--;
  }
  if ((var->flag == 'd' || var->flag == 'u') &&
      (var->precision > 0 && var->precision > var->length)) {
    int shift = var->precision - var->length;
    for (int k = var->precision; k >= 0; k--) {
      {
        if (integer[k] == '+' || integer[k] == '-') {
          integer[k] = '0';
        }
        integer[k + shift] = integer[k];
        integer[k] = '0';
      }
    }
    int i = 0;
    plus_minus_space(integer, var, &i);
  }
}

void print_str_to_str(char *str, variables *var, char *string) {
  if (string == NULL) {
    string = "(null)";
  }
  var->length = s21_strlen(string);
  default_settings(string, var);
  if (!var->minus_flag) {
    width_setup(str, var);
  }
  for (int i = 0; i < var->length; i++) {
    str[var->str_adress] = string[i];
    var->str_adress++;
  }
  if (var->minus_flag) {
    width_setup(str, var);
  }
}

void print_char_to_string(char *str, variables *var, char c) {
  var->length = 1;
  if (var->zero_flag) {
    var->zero_flag = 0;
  }
  if (!var->minus_flag) {
    width_setup(str, var);
  }
  str[var->str_adress] = c;
  var->str_adress++;
  if (var->minus_flag) {
    width_setup(str, var);
  }
}

void width_setup(char *str, variables *var) {
  int spaces = 0;
  if (var->width > var->length) {
    spaces = var->width - var->length;
  }
  for (int i = 0; i < spaces; i++) {
    if (!var->zero_flag || var->minus_flag) {
      str[var->str_adress] = ' ';
    } else if (var->zero_flag && var->flag != 's') {
      if (i == 0 && (var->plus_flag || var->is_negative)) {
        plus_minus_space(str, var, &var->str_adress);
        i++;
      }
      str[var->str_adress] = '0';
    }
    var->str_adress++;
  }
}

void plus_minus_space(char *string, variables *var, int *i) {
  if (var->space_flag || var->is_negative || var->plus_flag) {
    if (var->space_flag) {
      string[*i] = ' ';
    }
    if (var->zero_flag) {
      string[*i] = '0';
    }
    if (var->plus_flag) {
      string[*i] = '+';
    }
    if (var->is_negative) {
      string[*i] = '-';
    }
    (*i)++;
  }
}

void slash_parcer(char *str, char const *format, variables *var) {
  increase_format_adress(format, var);
  if (format[var->format_adress] == 'n') {
    str[var->str_adress] = '\n';
  } else if (format[var->format_adress] == 't') {
    str[var->str_adress] = '\t';
  }
  increase_format_adress(format, var);
  if (format[var->format_adress] == '\\') {
    slash_parcer(str, format, var);
  }
}

void percent_parser(const char *format, variables *var) {
  int space_count = 0;
  while (!end_of_parce(format[var->format_adress], &space_count, var) &&
         var->format_adress < (int)s21_strlen(format)) {
    width_parcer(format, var);
    point_parcer(format, var);
    precision_parcer(format, var);
    plus_flag_parcer(format, var);
    zero_flag_parcer(format, var);
    l_flag_parcer(format, var);
    h_flag_parcer(format, var);
    minus_flag_parcer(format, var);
    space_flag_parcer(format, var);
    increase_format_adress(format, var);
  }
  if (var->minus_flag == 1 && var->zero_flag == 1) {
    var->zero_flag = 0;
  }
  if (var->flag == 'u') {
    var->plus_flag = 0;
    var->space_flag = 0;
  }
}

int end_of_parce(char c, int *space_count, variables *var) {
  int result = 0;
  if (c == 'd') {
    var->flag = 'd';
    result = 1;
  } else if (c == 'c') {
    var->flag = 'c';
    result = 1;
  } else if (c == 'f') {
    var->flag = 'f';
    result = 1;
  } else if (c == 's') {
    var->flag = 's';
    result = 1;
  } else if (c == 'u') {
    var->flag = 'u';
    result = 1;
  } else if (c == '%') {
    if (*space_count != 1) {
      var->flag = '%';
      result = 1;
    }
  } else if (c == ' ') {
    (*space_count)++;
    if (*space_count == 2) {
      result = 1;
    }
  }
  return result;
}

void width_parcer(const char *format, variables *var) {
  if (format[var->format_adress] <= '9' && format[var->format_adress] >= '0' &&
      var->point_flag == 0) {
    var->width = var->width * 10 + char_to_digit(format[var->format_adress]);
  }
}

void point_parcer(const char *format, variables *var) {
  if (format[var->format_adress] == '.') {
    var->point_flag = 1;
    var->no_precision = 1;
    var->precision = 0;
  }
}

void precision_parcer(const char *format, variables *var) {
  if (format[var->format_adress] <= '9' && format[var->format_adress] >= '0' &&
      var->point_flag) {
    var->no_precision = 0;
    var->precision =
        var->precision * 10 + char_to_digit(format[var->format_adress]);
  }
}

void plus_flag_parcer(const char *format, variables *var) {
  if (format[var->format_adress] == '+' &&
      (format[var->format_adress - 1] == '%' ||
       format[var->format_adress - 1] == '0' ||
       format[var->format_adress - 1] == '-' ||
       format[var->format_adress - 1] == ' ')) {
    var->plus_flag = 1;
  }
}

void zero_flag_parcer(const char *format, variables *var) {
  if (format[var->format_adress] == '0' &&
      (format[var->format_adress - 1] == '%' ||
       format[var->format_adress - 1] == '+' ||
       format[var->format_adress - 1] == ' ' ||
       format[var->format_adress - 1] == '-')) {
    var->zero_flag = 1;
  }
}
void l_flag_parcer(const char *format, variables *var) {
  if (var->format_adress < (int)s21_strlen(format)) {
    if (format[var->format_adress] == 'l' &&
        end_of_parce(format[var->format_adress + 1], NULL, var)) {
      var->l_flag = 1;
    }
  }
}

void h_flag_parcer(const char *format, variables *var) {
  if (var->format_adress < (int)s21_strlen(format)) {
    if (format[var->format_adress] == 'h' &&
        end_of_parce(format[var->format_adress + 1], NULL, var)) {
      var->h_flag = 1;
    }
  }
}

void minus_flag_parcer(const char *format, variables *var) {
  if (format[var->format_adress] == '-') {
    var->minus_flag = 1;
  }
}
void space_flag_parcer(const char *format, variables *var) {
  if (format[var->format_adress] == ' ') {
    var->space_flag = 1;
  }
}

int char_to_digit(char c) {
  int result = 0;
  if (c == '1') {
    result = 1;
  } else if (c == '2') {
    result = 2;
  } else if (c == '3') {
    result = 3;
  } else if (c == '4') {
    result = 4;
  } else if (c == '5') {
    result = 5;
  } else if (c == '6') {
    result = 6;
  } else if (c == '7') {
    result = 7;
  } else if (c == '8') {
    result = 8;
  } else if (c == '9') {
    result = 9;
  } else if (c == '0') {
    result = 0;
  }
  return result;
}

void restore_variables(variables *var) {
  var->flag = 0;
  var->precision = -1;
  var->width = 0;
  var->plus_flag = 0;
  var->zero_flag = 0;
  var->is_negative = 0;
  var->l_flag = 0;
  var->h_flag = 0;
  var->minus_flag = 0;
  var->space_flag = 0;
  var->point_flag = 0;
  var->no_precision = 0;
}

void increase_format_adress(char const *format, variables *var) {
  if (var->format_adress < (int)s21_strlen(format)) {
    var->format_adress++;
  }
}

void default_settings(char *string, variables *var) {
  if (var->flag == 's' && var->precision != -1 &&
      var->precision < var->length) {
    var->length = var->precision;
  } else if (var->flag == 's' && var->precision == -1) {
    var->length = (int)s21_strlen(string);
  }
  if (var->width == 0 || var->width < var->length) {
    var->width = var->length;
  }
}

void print_empty(char *str, variables *var) {
  if (var->space_flag) {
    var->width++;
  }
  for (int i = 0; i < var->width; i++) {
    str[var->str_adress] = ' ';
    var->str_adress++;
  }
}

void big_double(double number, char *float_point, int *i) {
  int e = log10(number);
  for (int j = 0; j < e; j++) {
    number /= 10;
  }
  while (*i <= e) {
    int temp = (int)number;
    float_point[(*i)++] = temp + '0';
    number = (number * 10) - (temp * 10);
  }
}

void after_point_to_ascii(double after_point, variables *var, char *float_point,
                          int *i) {
  for (int j = 0; j < var->precision + 1; j++) {
    after_point *= 10;
    int digit = (int)after_point;
    float_point[(*i)++] = digit + '0';
    after_point -= digit;
  }
}

void place_point_in_place(char *float_point, int point_position, int *i,
                          variables *var) {
  if (var->precision > 0 || (var->precision = 0 && var->no_precision == 0)) {
    for (int k = *i; k > point_position; k--) {
      float_point[k] = float_point[k - 1];
    }
    float_point[point_position] = '.';
    (*i)++;
  }
}

char *create_a_demonic_bottom() {
  char *string = (char *)malloc(200 * sizeof(char));
  for (int i = 0; i < 200; i++) {
    string[i] = '\0';
  }
  return string;
}