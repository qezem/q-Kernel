#include "drivers/serial.h"
#include "gdt.h"
#include "libs/stdio.h"

void kernel_panic(const char *err) { write_string_serial(err); }

void kmain(void) {
  if (gdt_init() != 0) {
    __asm__ volatile("cli");

    while (1) {
      __asm__ volatile("hlt");
    }
  }

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
