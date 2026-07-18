#include "kernel.h"
#include "drivers/serial.h"
#include "drivers/vga.h"
#include "gdt.h"
#include "idt.h"
#include "libs/stdio.h"

void kernel_panic(const char *err) {
  clear_buffer();
  write_string_serial(err);
  kprint_string(err);
  __asm__ volatile("cli");

  while (1) {
    __asm__ volatile("hlt");
  }
}

void kmain(void) {
  if (gdt_init() != 0) {
    __asm__ volatile("cli");

    while (1) {
      __asm__ volatile("hlt");
    }
  }

  if (idt_init() == IDT_ERR_PTR_INVALID) {
    kernel_panic("IDT Error: ptr invalid");
  } else {
    write_string_serial("IDT initialized successfully!\n");
  }

  __asm__ volatile("int $0x03");

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

  volatile int a = 10;
  volatile int b = 0;
  int c = a / b;
}
