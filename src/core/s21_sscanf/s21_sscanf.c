#include "../../s21_string.h"

int s21_scanf(const char *str, const char *format, ...) {
  int res = 0;
  ops options = {0, 0, 0, 0, 0, 0, 0, '\0'};
  char *tmp = malloc((s21_strlen(str) + 1) * sizeof(char));
  if (!tmp) {
    printf("ERROR");
  } else {

  }
}




long s21_atoi(char *str, char **strlim, int base) {
                                // Эта функция преобразует строку str в целое число с заданным основанием base.
                                // Внутри функции:
                                // Пропускаются начальные пробелы и знаки.
                                // Определяется основание (если не указано, используется десятичное).
                                // Происходит парсинг числа в соответствии с основанием.
                                // Возвращается полученное целое число
  char *start = str;
  long int result = 0;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    str++;
  if (*str == '+') str++;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (base == 0 && *str == '0' && *(str + 1) == 'x')
    base = 16;
  else if (base == 0 && *str == '0')
    base = 8;
  else if (base == 0)
    base = 10;
  if (base == 16 && *str == '0' && *(str + 1) == 'x') str += 2;
  if (base == 10) {
    for (; *str >= '0' && *str <= '9'; str++, result *= 10) result += *str - 48;
    result /= 10;
  } else if (base == 8) {
    for (; *str >= '0' && *str <= '9'; str++, result *= 8) result += *str - 48;
    result /= 8;
  } else if (base == 16) {
    for (; (*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') ||
           (*str >= 'a' && *str <= 'f');
         str++, result *= 16) {
      if (*str >= '0' && *str <= '9')
        result += *str - 48;
      else if ((*str >= 'A' && *str <= 'F'))
        result += +*str - 55;
      else
        result += +*str - 87;
    }
    result /= 16;
  }
  if (strlim) *strlim = start + (str - start);
  return sign * result;
}


unsigned long s21_atoul(char *str, char **strlim, int base) {
                            // Эта функция аналогична s21_atoi, но возвращает беззнаковое целое число.
}

float s21_atof(char *str, char **strlim) {
                                        // Эта функция преобразует строку str в число с плавающей точкой.
                                        // Внутри функции:
                                        // Пропускаются начальные пробелы и знаки.
                                        // Происходит парсинг целой части и десятичной части числа.
                                        // Обрабатывается экспоненциальная запись (если есть).
                                        // Возвращается полученное число.

}

double s21_atod(char *str, char **strlim) {
                                // Эта функция преобразует строку str в число с плавающей точкой типа double.
                                // Внутри функции:
                                // Пропускаются начальные пробелы и знаки.
                                // Происходит парсинг целой части и десятичной части числа.
                                // Обрабатывается экспоненциальная запись (если есть).
                                // Возвращается полученное число.
}

long double s21_atold (char **str, char **strlin) {
                    // Эта функция аналогична s21_atod, но возвращает число с плавающей точкой типа long double.
}

int opd(va_list args, ops *op, char **src, int base) {
                                            // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                            // Внутри функции:
                                            // Проверяется буфер и пропускаются начальные пробелы и знаки.
                                            // Происходит парсинг целого числа в соответствии с заданным основанием.
                                            // Результат записывается в соответствующий аргумент.
                                            // Возвращается количество успешно прочитанных элементов.
}

int opu(va_list args, ops *op, char **src, int base) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Внутри функции:
                                        // Проверяется буфер и пропускаются начальные пробелы и знаки.
                                        // Происходит парсинг беззнакового целого числа в соответствии с заданным основанием.
                                        // Результат записывается в соответствующий аргумент.
                                        // Возвращается количество успешно прочитанных элементов.
}

int opf(va_list args, ops *op, char **src) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Внутри функции:
                                        // Проверяется буфер и пропускаются начальные пробелы и знаки.
                                        // Происходит парсинг числа с плавающей точкой в соответствии с заданным форматом.
                                        // Результат записывается в соответствующий аргумент.
                                        // Возвращается количество успешно прочитанных элементов.
}

int opp(va_list args, ops *op, char **src) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Внутри функции:
                                        // Проверяется буфер и пропускаются начальные пробелы и знаки.
                                        // Происходит парсинг беззнакового целого числа в шестнадцатеричной системе счисления.
                                        // Результат записывается в соответствующий аргумент.
                                        // Возвращается количество успешно прочитанных элементов.

}

int opc(va_list args, ops *op, char **src) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Внутри функции:
                                        // Если длина аргумента равна 2, то происходит преобразование символа в широкий символ.
                                        // Возвращается количество успешно прочитанных элементов.
}

int opst(va_list args, ops *op, char **src) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Внутри функции:
                                        // Создается новая строка new_str, куда копируется часть исходной строки.
                                        // Результаты записываются в соответствующие аргументы.
                                        // Возвращается количество успешно прочитанных элементов.
}

void oksym(char **src, ops *op) {
                                        // Эта функция пропускает начальные пробелы и другие символы, такие как перевод строки, табуляция и т. д.
                                        // Она используется для обработки входных строк, чтобы убедиться, что начальные символы не мешают дальнейшему анализу.
}

void oppe(char **src, ops *op, const char *format) {
                                        // Эта функция проверяет, соответствует ли текущий символ входной строке символу, указанному в формате.
                                        // Если символы совпадают, счетчик увеличивается, и указатель на строку продвигается.
                                        // В противном случае устанавливается флаг ошибки.

}

int optionsin(char **src, ops *op, const char *format) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Она проверяет, начинается ли формат с символа %, и если это так, устанавливает соответствующие флаги.
                                        // Также обрабатывается буфер, если он был установлен.
}

void opn(va_list args, ops *op) {
                                        // Эта функция используется для обработки аргументов внутри s21_sscanf.
                                        // Она записывает количество успешно прочитанных элементов в соответствующий аргумент.
}


void casenon(char **src, ops *op, const char *format) {
                                        // Эта функция обрабатывает символы, которые не являются частью формата.
                                        // Если символы совпадают с ожидаемым форматом, счетчик увеличивается.
}

int isbreak(va_list args, ops *op, char **src, const char *format) {
                                        // Эта функция проверяет, является ли текущая позиция в строке местом для завершения чтения.
                                        // Если это так, возвращается флаг завершения чтения.
}


int formatvsego(va_list args, ops *op, char **src, const char *format) {
    int res = 0;
  switch (*format) {
    case 'x':
    case 'X':
      res += opu(args, op, src, 16);
      break;
    case 'p':
      res += opp(args, op, src);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      res += opf(args, op, src);
      break;
    case 'c':
      res += opc(args, op, src);
      break;
    case 'd':
      res += opd(args, op, src, 10);
      break;
    case 'i':
      res += opd(args, op, src, 0);
      break;
    case 'o':
      res += opu(args, op, src, 8);
      break;
    case 's':
      res += opst(args, op, src);
      break;
    case 'u':
      res += opu(args, op, src, 10);
      break;
    case 'n':
      opn(args, op);
      break;
    case '%':
      oppe(src, op, format);
      break;
    case 'h':
      op->len = 1;
      break;
    case '*':
      op->supr = 1;
      break;
    case 'l':
      op->len = 2;
      break;
    case 'L':
      op->len = 3;
      break;
  }
  return res;
}

void check_buffer(char **src, ops *op) {
                                        // Эта функция проверяет буфер и устанавливает его, если он не установлен, а ширина (wid) задана и меньше длины строки.
                                        // Если буфер установлен, он восстанавливается на свою исходную позицию.
}