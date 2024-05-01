#include "../../s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
    char *pfl = (char *)format;
    char *strMem = (char *)str;
    va_list argp;
    va_start(argp, format);
    Holder *holderPointer;
    init(&holderPointer);
    int count = 0, flag = 0;
    while (*pfl != 0 && !flag) {
        if (*pfl != '%' && *pfl == *str) {
            str++;
            for (; *str == ' '; str++) {}
            pfl++;
        } else if (*pfl == ' ') {
            pfl++;
        } else if (*pfl == '%') {
            pfl++;
            int instruction = 0;
            while ((instruction = formatLineReader(&pfl)) != 0) {
                push(&holderPointer, instruction);
            }
            int mod = 0;
            int specifier = specifierReader(&pfl, &mod);
            if (specifier != 0) {
                int temp = getArg(&str, &argp, specifier, mod, &holderPointer, strMem);
                if (temp > 0) {
                    count++;
                } else if (temp < 0) {
                    flag++;
                }
            } else {
                // GENERATE ERROR
            }
        } else {
            flag++;
        }
    }
    destroy(&holderPointer);  // для гарантированной очистки стека
    va_end(argp);
    return count;
}

// Функция считывает и переводит строку в long int в зависимости от системы счисления radix.
long int s21_strtol(const char **str, Holder **holderPointer, int radix) {
    long int d = 0;
    int len = s21_strlen(*str);
    char *strCopy = (char *)malloc(len + 1);
    char *strMem = strCopy;
    s21_strcpy(strCopy, *str);

    int width = getWidth(holderPointer);
    char *fd = getFirstDigit(strCopy);
    if (width && len > width) {
        char mem = *(fd + width);
        *(fd + width) = 0;
        d = strtol(strCopy, &strCopy, radix);
        *(fd + width) = mem;
    } else {
        d = strtol(strCopy, &strCopy, radix);
    }
    *str += strCopy - strMem;

    free(strMem);
    return d;
}

// Функция считывает и переводит строку в long double независимо от нотации, в которой оно записано.
long double s21_strtold(const char **str, Holder **holderPointer) {
    long double f = 0;
    int len = s21_strlen(*str);
    char *strCopy = (char *)malloc(len + 1);
    char *strMem = strCopy;
    s21_strcpy(strCopy, *str);

    int width = getWidth(holderPointer);
    char *fd = getFirstDigit(strCopy);
    if (width && len > width) {
        char mem = *(fd + width);
        *(fd + width) = 0;
        f = strtold(strCopy, &strCopy);
        *(fd + width) = mem;
    } else {
        f = strtold(strCopy, &strCopy);
    }
    *str += strCopy - strMem;

    free(strMem);
    return f;
}

// Функция в зависимости от типа аргумента вызывает другие функции,
// Тип аргумента определяется из кода спецификатора type.
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
// В случае ошибки возвращается -1
int getArg(const char **str, va_list *argp, int type, int mod, Holder **holderPointer, char *strMem) {
    int set = 0;
    switch (type) {
        case 1:
            set = getCharacter(str, argp, holderPointer);
            break;
        case 2:
            set = getInteger(str, argp, holderPointer, mod, 10);
            break;
        case 3:
            set = getInteger(str, argp, holderPointer, mod, 0);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            set = getDouble(str, argp, holderPointer, mod);
            break;
        case 9:
            set = getInteger(str, argp, holderPointer, mod, 8);
            break;
        case 10:
            set = getString(str, argp, holderPointer);
            break;
        case 11:
            set = getInteger(str, argp, holderPointer, mod, 10);
            break;
        case 12:
            set = getInteger(str, argp, holderPointer, mod, 16);
            break;
        case 13:
            set = getInteger(str, argp, holderPointer, mod, 16);
            break;
        case 14:
            set = getPointer(str, argp, holderPointer);
            break;
        case 15:
            getNothing(str, argp, holderPointer, strMem);
            break;
        case 16:
            set = getPercent(str, holderPointer);
            break;
    }
    return set;
}

// Функция считывает из строки символ и сдвигает указатель на строку *str
// на необходимое количество символов вперед (если указана ширина)
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getCharacter(const char **str, va_list *argp, Holder **holderPointer) {
    int set = 0;
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
            set = 1;
        }
        (*str)++;
    }
    return set;
}

int getString(const char **str, va_list *argp, Holder **holderPointer) {
    int set = 0;
    int width = getWidth(holderPointer);
    if (width == 0) {
        width = s21_strlen(*str);
    }
    int asterisk = getAsterisk(holderPointer);
    char *arr = 0;
    if (!asterisk) {
        arr = (char *)va_arg(*argp, void *);
    }
    int i = 0;
    for (; **str == ' '; (*str)++) {}
    for (; i < width && **str && **str != ' '; i++) {
        if (!asterisk) {
            *(arr + i) = **str;
            set = 1;
        }
        (*str)++;
    }
    if (!asterisk) *(arr + i) = 0;

    return set;
}

// Функция считывает из строки число типа int и сдвигает указатель на строку *str
// на необходимое количество символов вперед
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getInteger(const char **str, va_list *argp, Holder **holderPointer, int mod, int radix) {
    int set = 0;
    char *fd = getFirstDigit(*str);
    if (*fd == '-' || *fd == '+') fd++;
    long int d = s21_strtol(str, holderPointer, radix);

    if (d != 0 || *fd == '0') {  // Если значение считано
        if (!getAsterisk(holderPointer)) {
            if (!mod) {
                *((int *)va_arg(*argp, void *)) = (int)d;
            } else if (mod == 1) {
                *((short *)va_arg(*argp, void *)) = (short)d;
            } else if (mod == 2) {
                *((long *)va_arg(*argp, void *)) = d;
            }
            set++;
        }
    } else {
        set--;
    }

    return set;
}

// Функция считывает из строки число типа double в любой нотации и сдвигает указатель на строку *str
// на необходимое количество символов вперед
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getDouble(const char **str, va_list *argp, Holder **holderPointer, int mod) {
    int set = 0;
    char *fd = getFirstDigit(*str);
    if (*fd == '-' || *fd == '+') fd++;
    long double f = s21_strtold(str, holderPointer);

    if (f != 0 || *fd == '0') {  // Если значение считано
        if (!getAsterisk(holderPointer)) {
            if (!mod) {
                *((float *)va_arg(*argp, void *)) = (float)f;
            } else if (mod == 3) {
                *((long double *)va_arg(*argp, void *)) = f;
            }
            set++;
        }
    } else {
        set--;
    }

    return set;
}

// Функция считывает из строки значение указателя в 16-ричной сс и сдвигает *str
// на необходимое количество символов вперед
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getPointer(const char **str, va_list *argp, Holder **holderPointer) {
    int set = 0;
    char *fd = getFirstDigit(*str);
    unsigned long p = s21_strtol(str, holderPointer, 16);
    if (p != 0 || *fd == '0') {
        if (!getAsterisk(holderPointer)) {
            *(va_arg(*argp, void **)) = (void *)p;
            set++;
        }
    } else {
        set--;
    }

    return set;
}

// Функция записывает по адресу аргумента количество встреченных до этого символов в строке
// Возвращает 1, если было присвоено значение аргументу и 0 - если нет.
int getNothing(const char **str, va_list *argp, Holder **holderPointer, const char *strMem) {
    int set = 0;
    getWidth(holderPointer);  // чтобы очистить стек в случае %5n
    if (!getAsterisk(holderPointer)) {
        *((int *)va_arg(*argp, void *)) = *str - strMem;
        set++;
    }
    return set;
}

// Функция считывает знак '%' из строки и сдвигает указатель *str
// В случае ошибки возвращается -1
int getPercent(const char **str, Holder **holderPointer) {
    int set = 0;
    getWidth(holderPointer);  // чтобы очистить стек в случае %5%
    getAsterisk(holderPointer);
    char *fd = getFirstDigit(*str);
    if (*fd != '%') set--;
    *str = fd + 1;
    return set;
}

// Функция возвращает ширину, если указана.
// Если ширина не указана, возвращает 0.
int getWidth(Holder **holderPointer) {
    int width = peek(holderPointer) - 8;
    if (width > 0) {
        pop(holderPointer);
    } else {
        width = 0;
    }
    return width;
}

// Функция возвращает указатель на первый символ числа (включая знак)
char *getFirstDigit(const char *str) {
    char *fd = (char *)str;
    for (; *fd == ' '; fd++) {
    }
    return fd;
}

// Функция возвращает 1, если в стеке есть операция "*"
int getAsterisk(Holder **holderPointer) {
    int ret = 0;
    if (isAny(*holderPointer, 6)) {
        pop(holderPointer);
        ret++;
    }
    return ret;
}

void init(Holder **holderPointer) { *holderPointer = s21_NULL;}

void push(Holder **holderPointer, int data) {
    Holder *temp = (Holder *)malloc(sizeof(Holder));
    temp->code = data;
    temp->next = *holderPointer;
    *holderPointer = temp;
}

int pop(Holder **holderPointer) {
    int ret = 0;
    if (*holderPointer != s21_NULL) {
        Holder *prev = *holderPointer;
        ret = prev->code;
        *holderPointer = (*holderPointer)->next;
        free(prev);
    }
    return ret;
}

int peek(Holder **holderPointer) {
    int ret = 0;
    if (*holderPointer != s21_NULL) {
        ret = (*holderPointer)->code;
    }
    return ret;
}

int isAny(Holder *holderPointer, int value) {
    int ret = 0;
    for (Holder *tempSP = holderPointer; tempSP; tempSP = tempSP->next) {
        if (tempSP->code == value) {
            ret++;
            break;
        }
    }
    return ret;
}

void destroy(Holder **holderPointer) {
    if (*holderPointer != s21_NULL) {
        while ((*holderPointer)->next) {
            Holder *prev = *holderPointer;
            *holderPointer = (*holderPointer)->next;
            free(prev);
        }
        free(*holderPointer);
    }
}

// Функция принимает в качестве аргумента адрес указателя на символ в форматной строке
// pointer to format line (PFL), считывает инструкцию и возвращает ее код.
// По окончании PFL указывает на следующий за прочтенной инструкцией символ.
// Когда встречается спецификатор (или модификатор), возвращает ноль.
int formatLineReader(char **pfl) {
    int code = 0;
    switch (**pfl) {
        case '-': code = 1; (*pfl)++; break;
        case '+': code = 2; (*pfl)++; break;
        case ' ': code = 3; (*pfl)++; break;
        case '#': code = 4; (*pfl)++; break;
        case '0': code = 5; (*pfl)++; break;
        case '*': code = 6; (*pfl)++; break;
        case '.':
            if (*(*pfl + 1) == '*') {
                code = 7;
                *pfl += 2;
            } else {
                (*pfl)++;
                code = -s21_atoi(pfl) - 1;
            }
            break;
        default:
            if (**pfl >= '0' && **pfl <= '9') {
                code = s21_atoi(pfl) + 8;
            }
            break;
    }
    return code;
}

// Функция преобразует число из строки в int, принимая адрес указателя на строку,
// начинающейся с первой цифры числа. Указатель по окончании работы функции будет указывать
// на первый символ после числа.
int s21_atoi(char **str) {
    int num = 0;
    if (**str >= '0' && **str <= '9') {
        num += **str - '0';
        (*str)++;
        for (char *ch = *str; *ch >= '0' && *ch <= '9'; ch++) {
            num *= 10;
        }
        num += s21_atoi(str);
    }
    return num;
}

// Функция принимает в качестве аргумента адрес указателя на первый символ спецификатора
// pointer to format line (PFL), считывает спецификатор и возвращает его код.
// По окончании PFL указывает на следующий за спецификатором символ.
// В случае ошибки возвращает ноль.
int specifierReader(char **pfl, int *mod) {
    int code = 0;
    switch (**pfl) {
        // Modifiers
        case 'h': *mod = 1; (*pfl)++; break;
        case 'l': *mod = 2; (*pfl)++; break;
        case 'L': *mod = 3; (*pfl)++; break;
    }
    switch (**pfl) {
        // Specifiers
        case 'c': code = 1; (*pfl)++; break;
        case 'd': code = 2; (*pfl)++; break;
        case 'i': code = 3; (*pfl)++; break;
        case 'e': code = 4; (*pfl)++; break;
        case 'E': code = 5; (*pfl)++; break;
        case 'f': code = 6; (*pfl)++; break;
        case 'g': code = 7; (*pfl)++; break;
        case 'G': code = 8; (*pfl)++; break;
        case 'o': code = 9; (*pfl)++; break;
        case 's': code = 10; (*pfl)++; break;
        case 'u': code = 11; (*pfl)++; break;
        case 'x': code = 12; (*pfl)++; break;
        case 'X': code = 13; (*pfl)++; break;
        case 'p': code = 14; (*pfl)++; break;
        case 'n': code = 15; (*pfl)++; break;
        case '%': code = 16; (*pfl)++; break;
    }
    return code;
}