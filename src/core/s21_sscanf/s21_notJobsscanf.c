// #include "../../s21_string.h"


// int s21_sscanf(const char *str, const char *format, ...) {
//   // char *iter_ster = (char *)format;
//   // char *strMem = (char *)str;
//   va_list args;
//   va_start(args, format);
//   option options = {0,0,0,0,0,0,0, '\0'};
//   // Holder *holderPointer;
//   // init (&holderPointer);
//   int result = 0, flags = 0;
//   char *tmp = malloc((s21_strlen(str) + 1) * sizeof(char));
//   if (!tmp) {
//     printf("ERROR");
//   } else {
//     tmp = s21_strcpy(tmp, str);
//     probel(&tmp, &options);
//     if (!*tmp) options.end = 1;
//     tmp = s21_strcpy(tmp - options.count, str);
//     options.count = 0;
//     for (; *format; format++) {
//     if (optionsin(&tmp, &options, format)) continue;
//     if(options.format) {
//       if((int) *format > 47 && (int) *format < 58) {
//         options.wid = options.wid * 10 + (int) *format - 48;
//         continue;
//       }
//       result += processformat(args, &options, &tmp, format);
//     } else {
//       sravnenie(&tmp, &options, format);
//     }
//     if (!isenough(args, &options, &tmp, format)) { 
//       if (!result && options.end) result = -1;
//       break;
//     }
//     }
//     free(tmp - options.count);
//     va_end(args);
//   }
//   return result;
// }


// // Функция считывает из строки число типа int и сдвигает указатель на строку *str
// // на необходимое количество символов вперед
// // Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
// int getInteger(va_list args, option *options, char **src, int base) {
//   int result = 0;
//   char *strlim;
//   check_buffer(src, options);
//   if (s21_atoi(*src, s21_NULL, base) ||
//       *(*src + s21_strspn(*src, "\n\t \f\x0B\r+-")) == '0') {
//     if (!options->zvezd) {
//       result++;
//       if (options->len == 1)
//         *(short int *)va_arg(args, void *) = s21_atoi(*src, &strlim, base);
//       else if (options->len == 2)
//         *(long int *)va_arg(args, void *) = s21_atoi(*src, &strlim, base);
//       else
//         *(int *)va_arg(args, void *) = s21_atoi(*src, &strlim, base);
//     } else {
//       s21_atoi(*src, &strlim, base);
//     }
//     options->count += strlim - *src;
//     *src = strlim;
//   } else {
//     options->err = 1;
//   }
//   options->format = 0;
//   return result;
// }
// //     while (*iter_ster != '\0' && !flags) {
// //       if (*iter_ster != '%' && *iter_ster == *str) {
// //         str++;
// //         for (; *str == ' '; str++) {}
// //       iter_ster++;
// //       } else if (*iter_ster == ' ') {
// //         iter_ster++;
// //       } else if (*iter_ster == '%') {
// //         iter_ster++;
// //         int todo = 0;
// //         while ((todo = FormatLineReader(&iter_ster)) != 0) {
// //           push(&holderPointer, todo);
// //         }
// //         int mode = 0;
// //         int spec = specifierReader(&iter_ster, &mode);
// //         if (spec != 0) {
// //           int temp = getArg(&str, &args, spec, mode, &holderPointer, strMem);
// //           if (temp > 0) {
// //             count++;
// //           } else if (temp < 0) {
// //             flags++;
// //           }
// //         } else {
// //           // ERROR
// //         }
// //       } else {
// //         flags++;
// //       }
// //     }
// //     destroy(&holderPointer); // чтобы точно очистить стэк
// //     va_end(args);
// //   return count;
// // }

// void sravnenie(char **src, option *options, const char *format) {
//   if (*format == ' ' || *format == '\t' || *format == '\n' || *format == '\r' ||
//       *format == '\x0B') {
//         while (**src == *format) {
//           (*src)++;
//           options -> count++;
//         }
//       } else if (**src == *format) {
//         (*src)++;
//         options -> count++;
//       } else {
//         options->err = 1;
//       }
// }

// int isenough(va_list args, option *options,char **src, const char *format) {
//   int result = 0;
//   va_list backup;
//   va_copy(backup, args);
//   if ((!**src && !options->buff && (s21_strstr(format, "%n") != s21_strchr(format, '%') || !s21_strstr(format, '%n'))) || !va_arg(backup, void *) || options->err) {
//     result = 1;
//   }
//   va_end(backup);
//   return result;
// }

// // Функция считывает знак '%' из строки и сдвигает указатель *str
// // В случае ошибки возвращается -1

// int GetPercent(const char **str, Holder **holderPointer) {
//   int *percent = 0;
//   getWidth(holderPointer); // Clean steck if < 5%
//   getAsterisk(holderPointer);
//   char *firstpointer = getFirstDigit(*str);
//   if (*firstpointer != '%') percent--;
//   *str = *firstpointer + 1;
//   return percent;
// }

// // Функция считывает из строки число типа double в любой нотации и сдвигает указатель на строку *str
// // на необходимое количество символов вперед
// // Возвращает 1, если было присвоено значение аргументу и 0 - если нет.

// int getDouble(const char **str, va_list *argp, Holder **holderPointer, int mod) {
//     int status = 0;
//     char *fd = getFirstDigit(*str);
//     if (*fd == '-' || *fd == '+') fd++;
//     long double f = s21_strtold(str, holderPointer);

//     if (f != 0 || *fd == '0') {  // Если значение считано
//         if (!getAsterisk(holderPointer)) {
//             if (!mod) {
//                 *((float *)va_arg(*argp, void *)) = (float)f;
//             } else if (mod == 3) {
//                 *((long double *)va_arg(*argp, void *)) = f;
//             }
//             status++;
//         }
//     } else {
//         status--;
//     }

//     return status;
// }


// long double s21_strtold(const char **str, Holder **holderPointer) {
//     long double first = 0;
//     int len = s21_strlen(*str);
//     char *strCopy = (char *)malloc(len + 1);
//     char *strMem = strCopy;
//     s21_strcpy(strCopy, *str);

//     int width = getWidth(holderPointer);
//     char *fd = getFirstDigit(strCopy);
//     if (width && len > width) {
//         char mem = *(fd + width);
//         *(fd + width) = 0;
//         first = strtold(strCopy, &strCopy);
//         *(fd + width) =  mem;
//     } else {
//       first = strtold(strCopy, &strCopy);
//     }
//     *str += strCopy - strMem;
    
//     free(strMem);
//     return first;
// }

// // Функция в зависимости от типа аргумента вызывает другие функции,
// // Тип аргумента определяется из кода спецификатора type.
// // Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
// // В случае ошибки возвращается -1


// void probel(char **src, option *propusk) {
//   while (**src == ' ' || **src == '\t' || **src == '\n ' || **src == '\r' || **src == '\x0B' || **src == '\f') {
//     (*src)++;
//     propusk -> count++;
//   }
// }

// int getArg(const char **str, va_list *argp, int type, int mod, option *options, Holder **holderPointer, char *strMem) {
//     int status = 0;
//     switch (type) {
//         case '1':
//             status = getCharacter(str, argp, holderPointer);
//             break;
//         case '2':
//             status = getInteger(argp, options, str, 10);
//             break;
//         case '3':
//             status = getInteger(argp, options, str, 0);
//             break;
//         case '4':
//         case '5':
//         case '6':
//         case '7':
//         case '8':
//             status = getDouble(str, argp, holderPointer, mod);
//             break;
//         case '9':
//             status = opu(argp, options, str, 8);
//             break;
//         case '10':
//             status = getString(str, argp, holderPointer);
//             break;
//         case '11':
//             status = opu(argp, options, str, 10);
//             break;
//         case '12':
//             status = opu(argp, options, str, 16);
//             break;
//         case '13':
//             status = opu(argp, options, str, 16);
//             break;
//         case '14':
//             status = getPointer(str, argp, holderPointer);
//             break;
//         case '15':
//             getNothing(str, argp, holderPointer, strMem);
//             break;
//         case '16':
//             status = getPercent(str, holderPointer);
//             break;
//     }
//     return status;
// }


// // Функция записывает по адресу аргумента количество встреченных до этого символов в строке
// // Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
// int getNothing(const char **str, va_list *argp, Holder **holderPointer, const char *strMem) {
//     int status = 0;
//     getWidth(holderPointer);  // чтобы очистить стек в случае %5n
//     if (!getAsterisk(holderPointer)) {
//         *((int *)va_arg(*argp, void *)) = *str - strMem;
//         status++;
//     }
//     return status;
// }

// // Функция считывает из строки символ и сдвигает указатель на строку *str
// // на необходимое количество символов вперед (если указана ширина)
// // Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
// int getCharacter(const char **str, va_list *argp, Holder **holderPointer) {
//     int status = 0;
//     int width = getWidth(holderPointer);
//     if (width == 0) {
//         width = 1;
//     }
//     int asterisk = getAsterisk(holderPointer);
//     char *arr = 0;
//     if (!asterisk) {
//         arr = (char *)va_arg(*argp, void *);
//     }
//     for (int i = 0; i < width && **str; i++) {
//         if (!asterisk) {
//             *(arr + i) = **str;
//             status = 1;
//         }
//         (*str)++;
//     }
//     return status;
// }

// int optionsin(char **src, option *options, const char *format) {
//   int result = 0;
//   if (*format == '%' && !options->format) {
//     result++;
//     options->format = 1;
//     options->zvezd = 0;
//     options->len = 0;
//     if (options->buff) {
//       *(*src + s21_strlen(*src)) = options->buff;
//       options->buff = '\0';
//     }
//     options->wid = 0;
//   }
//   return result;
// }

// double s21_atod(char *str, char **strlim) {
//   char *start = str;
//   double a, decplace, b;
//   int sign = 1;
//   while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
//          *str == '\x0B' || *str == '\f')
//     ++str;
//   if (*str == '+') ++str;
//   if (*str == '-') {
//     sign = -1;
//     ++str;
//   }
//   for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
//   if (*str == '.') ++str;
//   for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
//     a = a * 10. + (*str - '0');
//   if (*str == 'e' || *str == 'E') {
//     int esign = 1;
//     if (a <= 1e-6) a = 1;
//     ++str;
//     if (*str == '-') {
//       esign = -1;
//       ++str;
//     }
//     if (*str == '+') ++str;
//     for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
//     b *= esign;
//   } else {
//     b = 0;
//   }
//   if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
//       (str[2] == 'n' || str[2] == 'N')) {
//     str += 3;
//     a = NAN * sign;
//   }
//   if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
//       (str[2] == 'f' || str[2] == 'F')) {
//     str += 3;
//     a = INFINITY * sign;
//   }
//   if (strlim) *strlim = start + (str - start);
//   return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
// }

// long double s21_atold(char *str, char **strlim) {
//   char *start = str;
//   long double a, decplace, b;
//   int sign = 1;
//   while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
//          *str == '\x0B' || *str == '\f')
//     ++str;
//   if (*str == '+') ++str;
//   if (*str == '-') {
//     sign = -1;
//     ++str;
//   }
//   for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
//   if (*str == '.') ++str;
//   for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
//     a = a * 10. + (*str - '0');
//   if (*str == 'e' || *str == 'E') {
//     int esign = 1;
//     if (a <= 1e-6) a = 1;
//     ++str;
//     if (*str == '-') {
//       esign = -1;
//       ++str;
//     }
//     if (*str == '+') ++str;
//     for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
//     b *= esign;
//   } else {
//     b = 0;
//   }
//   if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
//       (str[2] == 'n' || str[2] == 'N')) {
//     str += 3;
//     a = NAN * sign;
//   }
//   if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
//       (str[2] == 'f' || str[2] == 'F')) {
//     str += 3;
//     a = INFINITY * sign;
//   }
//   if (strlim) *strlim = start + (str - start);
//   return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
// }

// // Функция принимает в качестве аргумента адрес указателя на символ в форматной строке
// // pointer to format line (PFL), считывает инструкцию и возвращает ее код.
// // По окончании PFL указывает на следующий за прочтенной инструкцией символ.
// // Когда встречается спецификатор (или модификатор), возвращает ноль.
// int formatLineReader(char **pfl) {
//     int code = 0;
//     switch (**pfl) {
//         case '-': code = 1; (*pfl)++; break;
//         case '+': code = 2; (*pfl)++; break;
//         case ' ': code = 3; (*pfl)++; break;
//         case '#': code = 4; (*pfl)++; break;
//         case '0': code = 5; (*pfl)++; break;
//         case '*': code = 6; (*pfl)++; break;
//         case '.':
//             if (*(*pfl + 1) == '*') {
//                 code = 7;
//                 *pfl += 2;
//             } else {
//                 (*pfl)++;
//                 code = -s21_atoi(pfl) - 1;
//             }
//             break;
//         default:
//             if (**pfl >= '0' && **pfl <= '9') {
//                 code = s21_atoi(pfl) + 8;
//             }
//             break;
//     }
//     return code;
// }

// // Функция принимает в качестве аргумента адрес указателя на первый символ спецификатора
// // pointer to format line (PFL), считывает спецификатор и возвращает его код.
// // По окончании PFL указывает на следующий за спецификатором символ.
// // В случае ошибки возвращает ноль.
// int specifierReader(char **pfl, int *mod) {
//     int code = 0;
//     switch (**pfl) {
//         // Modifiers
//         case 'h': *mod = 1; (*pfl)++; break;
//         case 'l': *mod = 2; (*pfl)++; break;
//         case 'L': *mod = 3; (*pfl)++; break;
//     }
//     switch (**pfl) {
//         // Specifiers
//         case 'c': code = 1; (*pfl)++; break;
//         case 'd': code = 2; (*pfl)++; break;
//         case 'i': code = 3; (*pfl)++; break;
//         case 'e': code = 4; (*pfl)++; break;
//         case 'E': code = 5; (*pfl)++; break;
//         case 'f': code = 6; (*pfl)++; break;
//         case 'g': code = 7; (*pfl)++; break;
//         case 'G': code = 8; (*pfl)++; break;
//         case 'o': code = 9; (*pfl)++; break;
//         case 's': code = 10; (*pfl)++; break;
//         case 'u': code = 11; (*pfl)++; break;
//         case 'x': code = 12; (*pfl)++; break;
//         case 'X': code = 13; (*pfl)++; break;
//         case 'p': code = 14; (*pfl)++; break;
//         case 'n': code = 15; (*pfl)++; break;
//         case '%': code = 16; (*pfl)++; break;
//     }
//     return code;
// }

// int opu(va_list args, option *options, char **src, int base) {
//   int result = 0;
//   char *strlim;
//   check_buffer(src, options);
//   if (s21_atoul(*src, s21_NULL, base) ||
//       *(*src + s21_strspn(*src, "\n\t \f\x0B\r+")) == '0') {
//     if (!options->zvezd) {
//       if (s21_atoul(*src, s21_NULL, base) || **src == '0') result++;
//       if (options->len == 1)
//         *(short unsigned *)va_arg(args, void *) =
//             s21_atoul(*src, &strlim, base);
//       else if (options->len == 2)
//         *(long unsigned *)va_arg(args, void *) = s21_atoul(*src, &strlim, base);
//       else
//         *(unsigned *)va_arg(args, void *) = s21_atoul(*src, &strlim, base);
//     } else {
//       s21_atoul(*src, &strlim, base);
//     }
//     options->count += strlim - *src;
//     *src = strlim;
//   } else {
//     options->err = 1;
//   }
//   options->format = 0;
//   return result;
// }

// // Функция возвращает ширину, если указана.
// // Если ширина не указана, возвращает 0.
// int getWidth(Holder **holderPointer) {
//     int width = peek(holderPointer) - 8;
//     if (width > 0) {
//         pop(holderPointer);
//     } else {
//         width = 0;
//     }
//     return width;
// }

// // Функция возвращает указатель на первый символ числа (включая знак)
// char *getFirstDigit(const char *str) {
//     char *fd = (char *)str;
//     for (; *fd == ' '; fd++) {
//     }
//     return fd;
// }

// // Функция возвращает 1, если в стеке есть операция "*"
// int getAsterisk(Holder **holderPointer) {
//     int ret = 0;
//     if (isAny(*holderPointer, 6)) {
//         pop(holderPointer);
//         ret++;
//     }
//     return ret;
// }

// void init(Holder **holderPointer) { *holderPointer = s21_NULL;}

// void push(Holder **holderPointer, int data) {
//     Holder *temp = (Holder *)malloc(sizeof(Holder));
//     temp->code = data;
//     temp->next = *holderPointer;
//     *holderPointer = temp;
// }

// int pop(Holder **holderPointer) {
//     int ret = 0;
//     if (*holderPointer != s21_NULL) {
//         Holder *prev = *holderPointer;
//         ret = prev->code;
//         *holderPointer = (*holderPointer)->next;
//         free(prev);
//     }
//     return ret;
// }

// int peek(Holder **holderPointer) {
//     int ret = 0;
//     if (*holderPointer != s21_NULL) {
//         ret = (*holderPointer)->code;
//     }
//     return ret;
// }

// int isAny(Holder *holderPointer, int value) {
//     int ret = 0;
//     for (Holder *tempSP = holderPointer; tempSP; tempSP = tempSP->next) {
//         if (tempSP->code == value) {
//             ret++;
//             break;
//         }
//     }
//     return ret;
// }

// void destroy(Holder **holderPointer) {
//     if (*holderPointer != s21_NULL) {
//         while ((*holderPointer)->next) {
//             Holder *prev = *holderPointer;
//             *holderPointer = (*holderPointer)->next;
//             free(prev);
//         }
//         free(*holderPointer);
//     }
// }