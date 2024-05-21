#include "s21_strerror.h"

#include "s21_string.h"

char *s21_strerror(int errnum) {
  const char *
      *strerrors;  // A pointer to the appropriate array of error strings

#if defined(__APPLE__)
  strerrors = strerrors_mac;
#elif defined(__linux__)
  strerrors = strerrors_linux;
#endif

  return (char *)strerrors[errnum];
}
