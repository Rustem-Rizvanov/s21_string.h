#include "../../s21_string.h"


int s21_sscanf(const char *str, const char *format, ...) {
  // char *iter_ster = (char *)format;
  // char *strMem = (char *)str;
  va_list args;
  va_start(args, format);
  option options = {0,0,0,0,0,0,0, '\0'};
  // Holder *holderPointer;
  // init (&holderPointer);
  int result = 0, flags = 0;
  char *tmp = malloc((s21_strlen(str) + 1) * sizeof(char));
  if (!tmp) {
    printf("ERROR");
  } else {
    tmp = s21_strcpy(tmp, str);
    probel(&tmp, &options);
    if (!*tmp) options.end = 1;
    tmp = s21_strcpy(tmp - options.count, str);
    options.count = 0;
    for (; *format; format++) {
    if (optionsin(&tmp, &options, format)) continue;
    if(options.format) {
      if((int) *format > 47 && (int) *format < 58) {
        options.wid = options.wid * 10 + (int) *format - 48;
        continue;
      }
      result += processformat(args, &options, &tmp, format);
    } else {
      sravnenie(&tmp, &options, format);
    }
    if (!isenough(args, &options, &tmp, format)) { 
      if (!result && options.end) result = -1;
      break;
    }
    }
    free(tmp - options.count);
    va_end(args);
  }
  return result;
}


// Функция считывает из строки число типа int и сдвигает указатель на строку *str
// на необходимое количество символов вперед
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getInteger(va_list args, option *options, char **src, int base) {
  int result = 0;
  char *strlim;
  check_buffer(src, options);
  if (s21_atoi(*src, s21_NULL, base) ||
      *(*src + s21_strspn(*src, "\n\t \f\x0B\r+-")) == '0') {
    if (!options->zvezd) {
      result++;
      if (options->len == 1)
        *(short int *)va_arg(args, void *) = s21_atoi(*src, &strlim, base);
      else if (options->len == 2)
        *(long int *)va_arg(args, void *) = s21_atoi(*src, &strlim, base);
      else
        *(int *)va_arg(args, void *) = s21_atoi(*src, &strlim, base);
    } else {
      s21_atoi(*src, &strlim, base);
    }
    options->count += strlim - *src;
    *src = strlim;
  } else {
    options->err = 1;
  }
  options->format = 0;
  return result;
}
//     while (*iter_ster != '\0' && !flags) {
//       if (*iter_ster != '%' && *iter_ster == *str) {
//         str++;
//         for (; *str == ' '; str++) {}
//       iter_ster++;
//       } else if (*iter_ster == ' ') {
//         iter_ster++;
//       } else if (*iter_ster == '%') {
//         iter_ster++;
//         int todo = 0;
//         while ((todo = FormatLineReader(&iter_ster)) != 0) {
//           push(&holderPointer, todo);
//         }
//         int mode = 0;
//         int spec = specifierReader(&iter_ster, &mode);
//         if (spec != 0) {
//           int temp = getArg(&str, &args, spec, mode, &holderPointer, strMem);
//           if (temp > 0) {
//             count++;
//           } else if (temp < 0) {
//             flags++;
//           }
//         } else {
//           // ERROR
//         }
//       } else {
//         flags++;
//       }
//     }
//     destroy(&holderPointer); // чтобы точно очистить стэк
//     va_end(args);
//   return count;
// }

void sravnenie(char **src, option *options, const char *format) {
  if (*format == ' ' || *format == '\t' || *format == '\n' || *format == '\r' ||
      *format == '\x0B') {
        while (**src == *format) {
          (*src)++;
          options -> count++;
        }
      } else if (**src == *format) {
        (*src)++;
        options -> count++;
      } else {
        options->err = 1;
      }
}

int isenough(va_list args, option *options,char **src, const char *format) {
  int result = 0;
  va_list backup;
  va_copy(backup, args);
  if ((!**src && !options->buff && (s21_strstr(format, "%n") != s21_strchr(format, '%') || !s21_strstr(format, '%n'))) || !va_arg(backup, void *) || options->err) {
    result = 1;
  }
  va_end(backup);
  return result;
}

// Функция считывает знак '%' из строки и сдвигает указатель *str
// В случае ошибки возвращается -1

int GetPercent(const char **str, Holder **holderPointer) {
  int *percent = 0;
  getWidth(holderPointer); // Clean steck if < 5%
  getAsterisk(holderPointer);
  char *firstpointer = getFirstDigit(*str);
  if (*firstpointer != '%') percent--;
  *str = *firstpointer + 1;
  return percent;
}

// Функция считывает и переводит строку в long double независимо от нотации, в которой оно записано.


int getDouble(va_list args, option *options, char **src) {
  int result = 0;
  char *strlim;
  check_buffer(src, options);
  if (fabs(s21_atod(*src, s21_NULL)) >= 1e-100 ||
      isnan(s21_atod(*src, s21_NULL)) ||
      *(*src + s21_strspn(*src, "\n\t \f\x0B\r+-")) == '0') {
    if (!options->zvezd) {
      result++;
      if (options->len == 3)
        *(long double *)va_arg(args, void *) = s21_atold(*src, &strlim);
      else if (options->len == 2)
        *(double *)va_arg(args, void *) = s21_atod(*src, &strlim);
      else
        *(float *)va_arg(args, void *) = s21_atof(*src, &strlim);
    } else {
      s21_atof(*src, &strlim);
    }
    options->count += strlim - *src;
    *src = strlim;
  } else {
    options->err = 1;
  }
  options->format = 0;
  return result;
}


long double s21_strtold(const char **str, Holder **holderPointer) {
    long double first = 0;
    int len = s21_strlen(*str);
    char *strCopy = (char *)malloc(len + 1);
    char *strMem = strCopy;
    s21_strcpy(strCopy, *str);

    int width = getWidth(holderPointer);
    char *firstpointer = getFirstDigit(strCopy);
    if (width && len > width) {
        char mem = *(firstpointer + width);
        *(firstpointer + width) = 0;
        first = strTold(strCopy, &strCopy);
        *(firstpointer + width) =  mem;
    } else {
      first = strTold(strCopy, &strCopy);
    }
    *str += strCopy - strMem;
    
    free(strMem);
    return first;
}

// Функция в зависимости от типа аргумента вызывает другие функции,
// Тип аргумента определяется из кода спецификатора type.
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
// В случае ошибки возвращается -1


void probel(char **src, option *propusk) {
  while (**src == ' ' || **src == '\t' || **src == '\n ' || **src == '\r' || **src == '\x0B' || **src == '\f') {
    (*src)++;
    propusk -> count++;
  }
}

int getArg(const char **str, va_list *argp, int type, int mod, option *options, Holder **holderPointer, char *strMem) {
    int status = 0;
    switch (type) {
        case 'c':
            status = getCharacter(str, argp, holderPointer);
            break;
        case 'd':
            status = getInteger(str, argp, holderPointer, mod, 10);
            break;
        case 'i':
            status = getInteger(str, argp, holderPointer, mod, 0);
            break;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            status = getDouble(str, argp, holderPointer, mod);
            break;
        case 'o':
            status = getInteger(str, argp, holderPointer, mod, 8);
            break;
        case 's':
            status = getString(str, argp, holderPointer);
            break;
        case 'u':
            status = getInteger(str, argp, holderPointer, mod, 10);
            break;
        case 'x':
            status = getInteger(str, argp, holderPointer, mod, 16);
            break;
        case 'X':
            status = getInteger(str, argp, holderPointer, mod, 16);
            break;
        case 'p':
            status = getPointer(str, argp, holderPointer);
            break;
        case 'n':
            getNothing(str, argp, holderPointer, strMem);
            break;
        case '%':
            status = getPercent(str, holderPointer);
            break;
        case 'h':
          options->len = 1;
          break;
        case '*':
          options->zvezd = 1;
          break;
        case 'l':
          options->len = 2;
          break;
        case 'L':
          options->len = 3;
          break;
    }
    return status;
}


// Функция записывает по адресу аргумента количество встреченных до этого символов в строке
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getNothing(const char **str, va_list *argp, Holder **holderPointer, const char *strMem) {
    int status = 0;
    getWidth(holderPointer);  // чтобы очистить стек в случае %5n
    if (!getAsterisk(holderPointer)) {
        *((int *)va_arg(*argp, void *)) = *str - strMem;
        status++;
    }
    return status;
}

// Функция считывает из строки символ и сдвигает указатель на строку *str
// на необходимое количество символов вперед (если указана ширина)
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getCharacter(const char **str, va_list *argp, Holder **holderPointer) {
    int status = 0;
    int width = getWidth(holderPointer);
    if (width == 0) {
        width = 1;
    }
    int asterisk = getAsterisk(holderPointer);
    char *arr = 0;
    if (!asterisk) {
        arr = (char *)va_arg(*argp, void *);
    }
    for (int i = 0; i < width && **str; i++) {
        if (!asterisk) {
            *(arr + i) = **str;
            status = 1;
        }
        (*str)++;
    }
    return status;
}

int optionsin(char **src, option *options, const char *format) {
  int result = 0;
  if (*format == '%' && !options->format) {
    result++;
    options->format = 1;
    options->zvezd = 0;
    options->len = 0;
    if (options->buff) {
      *(*src + s21_strlen(*src)) = options->buff;
      options->buff = '\0';
    }
    options->wid = 0;
  }
  return result;
}

double s21_atod(char *str, char **strlim) {
  char *start = str;
  double a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    ++str;
  if (*str == '+') ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  }
  for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
  if (*str == '.') ++str;
  for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int esign = 1;
    if (a <= 1e-6) a = 1;
    ++str;
    if (*str == '-') {
      esign = -1;
      ++str;
    }
    if (*str == '+') ++str;
    for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
    b *= esign;
  } else {
    b = 0;
  }
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) {
    str += 3;
    a = NAN * sign;
  }
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) {
    str += 3;
    a = INFINITY * sign;
  }
  if (strlim) *strlim = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

long double s21_atold(char *str, char **strlim) {
  char *start = str;
  long double a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    ++str;
  if (*str == '+') ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  }
  for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
  if (*str == '.') ++str;
  for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int esign = 1;
    if (a <= 1e-6) a = 1;
    ++str;
    if (*str == '-') {
      esign = -1;
      ++str;
    }
    if (*str == '+') ++str;
    for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
    b *= esign;
  } else {
    b = 0;
  }
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) {
    str += 3;
    a = NAN * sign;
  }
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) {
    str += 3;
    a = INFINITY * sign;
  }
  if (strlim) *strlim = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}
