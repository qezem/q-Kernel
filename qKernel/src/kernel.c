#include "kernel.h"
#include "drivers/keyboard.h"
#include "drivers/serial.h"
#include "drivers/vga.h"
#include "gdt.h"
#include "idt.h"
#include "libs/stdio.h"
#include "pic.h"

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
  __asm__ volatile("cli");

  if (gdt_init() != 0) {
    __asm__ volatile("cli");

    while (1) {
      __asm__ volatile("hlt");
    }
  }

  idt_init();

  pic_init();
  if (init_serial() == 1) {
    printf("Serial initialization failed!\n");
  } else {
    write_string_serial("Serial initialized successfully!\n");
  }

  keyboard_init();

  __asm__ volatile("sti");

  printf("Kernel is working!\n");
  write_string_serial("VGA driver is working!\n");
  printf("%d %d %c %s", 6, 7, 'c', "String\n");
  puts("puts function");
  putchar(1);
}
