#include "stdio.h"
#include "drivers/VGA_driver/vga.h"
#include <stdarg.h>

void printf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);

  int sum = 0;

  for (int i = 0; format[i] != '\0'; ++i) {
    if (format[i] == '%') {
      ++i;

      if (format[i] == 'd') {
        kprint_int(va_arg(ap, int));
      } else if (format[i] == 'c') {
        kprint_char((char)va_arg(ap, int));
      } else if (format[i] == 's') {
        kprint_string(va_arg(ap, char *));
      }
    } else {
      kprint_char(format[i]);
    }
  }

  va_end(ap);
}
