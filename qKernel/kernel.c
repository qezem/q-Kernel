#include "drivers/serial/serial.h"
#include "libs/stdio/stdio.h"

void kmain(void) {
  if (init_serial() == 1) {
    printf("Serial initialization failed!\n");
  } else {
    write_string_serial("Serial initialized successfully!\n");
  }

  printf("Kernel is working!\n");
  write_string_serial("VGA driver is working!\n");
  printf("%d %d %c %s", 6, 7, 'c', "String\n");
  puts("puts function");
  putchar(1);
}
