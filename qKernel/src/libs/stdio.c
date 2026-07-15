#include "libs/stdio.h"
#include "drivers/vga.h"
#include <stdarg.h>
#include <stddef.h>

int printf(const char *format, ...) {
  if (format == NULL) {
    return EOF;
  }

  va_list ap;
  va_start(ap, format);

  int count = 0;

  for (int i = 0; format[i] != '\0'; ++i) {
    if (format[i] == '%') {
      ++i;

      if (format[i] == 'd' || format[i] == 'i') {
        count += kprint_int(va_arg(ap, int));
      } else if (format[i] == 'c') {
        kprint_char((char)va_arg(ap, int));
        ++count;
        ++count;
      } else if (format[i] == 's') {
        count += kprint_string(va_arg(ap, char *));
      }
    } else {
      kprint_char(format[i]);
      ++count;
    }
  }

  va_end(ap);

  return count;
}

int putchar(int character) {
  kprint_char((char)character);
  return character;
}

int puts(const char *str) {
  kprint_string(str);
  kprint_char('\n');

  return 0;
}
