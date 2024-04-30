#include <../../s21_string.h>


int s21_sscanf(const char *str, const char *format, ...) {
  char *iter_ster = (char *)format;
  char *strMem = (char *)str;
  va_list args;
  va_start(args, format);
  Holder *holderPointer;
  init (&holderPointer);
  int count = 0, flags = 0;
    while (*iter_ster != '\0' && !flags) {
      if (*iter_ster != '%' && *iter_ster == *str) {
        str++;
        for (; *str == ' '; str++) {}
      iter_ster++;
      } else if (*iter_ster == ' ') {
        iter_ster++;
      } else if (*iter_ster == '%') {
        iter_ster++;
        int todo = 0;
        while ((todo = FormatLineReader(&iter_ster)) != 0) {
          push(&holderPointer, todo);
        }
        int mode = 0;
        int spec = specifierReader(&iter_ster, &mode);
        if (spec != 0) {
          int temp = getArg(&str, &args, spec, mode, &holderPointer, strMem);
          if (temp > 0) {
            count++;
          } else if (temp < 0) {
            flags++;
          }
        } else {
          // ERROR
        }
      } else {
        flags++;
      }
    }
    destroy(&holderPointer); // чтобы точно очистить стэк
    va_end(args);
  return count;
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


long double s21_strtold(const char **str, Holder **stackPointer) {
    long double f = 0;
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

int getArg(const char **str, va_list *argp, int type, int mod, Holder **stackPointer, char *strMem) {
    int status = 0;
    switch (type) {
        case 1:
            status = getCharacter(str, argp, stackPointer);
            break;
        case 2:
            status = getInteger(str, argp, stackPointer, mod, 10);
            break;
        case 3:
            status = getInteger(str, argp, stackPointer, mod, 0);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            status = getDouble(str, argp, stackPointer, mod);
            break;
        case 9:
            status = getInteger(str, argp, stackPointer, mod, 8);
            break;
        case 10:
            status = getString(str, argp, stackPointer);
            break;
        case 11:
            status = getInteger(str, argp, stackPointer, mod, 10);
            break;
        case 12:
            status = getInteger(str, argp, stackPointer, mod, 16);
            break;
        case 13:
            status = getInteger(str, argp, stackPointer, mod, 16);
            break;
        case 14:
            status = getPointer(str, argp, stackPointer);
            break;
        case 15:
            getNothing(str, argp, stackPointer, strMem);
            break;
        case 16:
            status = getPercent(str, stackPointer);
            break;
    }
    return status;
}

// Функция считывает из строки символ и сдвигает указатель на строку *str
// на необходимое количество символов вперед (если указана ширина)
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getCharacter(const char **str, va_list *argp, Stack **stackPointer) {
    int status = 0;
    int width = getWidth(stackPointer);
    if (width == 0) {
        width = 1;
    }
    int asterisk = getAsterisk(stackPointer);
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
