#include "drivers/serial.h"
#include "libs/io.h"

int init_serial(void) {
  outb(COM1 + 1, 0x00);
  outb(COM1 + 3, 0x80);
  outb(COM1 + 0, 0x03);
  outb(COM1 + 1, 0x00);
  outb(COM1 + 3, 0x03);
  outb(COM1 + 2, 0xc7);
  outb(COM1 + 4, 0x0b);
  outb(COM1 + 4, 0x1e);

  outb(COM1 + 0, 0xae);
  if (inb(COM1 + 0) != 0xae) {
    return 1;
  }

  outb(COM1 + 4, 0x0f);
  return 0;
}

int is_transmit_empty() { return inb(COM1 + 5) & 0x20; }

int serial_received() { return inb(COM1 + 5) & 0x01; }

void write_serial(char c) {
  while (is_transmit_empty() == 0)
    ;
  outb(COM1 + 0, c);
}

void write_string_serial(const char *str) {
  for (int i = 0; str[i] != '\0'; ++i) {
    write_serial(str[i]);
  }
}

char read_serial(void) {
  while (serial_received() == 0)
    ;
  return inb(COM1 + 0);
}
