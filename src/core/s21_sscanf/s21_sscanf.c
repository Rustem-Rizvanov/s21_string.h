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
