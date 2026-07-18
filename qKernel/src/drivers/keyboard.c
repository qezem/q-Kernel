#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "isr.h"
#include "libs/io.h"
#include <stdint.h>

unsigned char key_map[] = {
    0,   0,    '1',  '2', '3',  '4', '5', '6', '7', '8', '9', '0', '-',
    '=', '\b', 2,    'q', 'w',  'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    '[', ']',  '\n', 3,   'a',  's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`',  4,   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
    '.', '/',  4,    '*', 5,    ' ', 6,   0,   0,   0,   0,   0,   0,
    0,   0,    0,    0,   0,    0,   '7', '8', '9', '-', '4', '5', '6',
    '+', '1',  '2',  '3', '0',  '.', 0,   0};

void keyboard_callback(struct registers *regs) {
  unsigned char scancode = inb(0x60);
  if (scancode < 0x80) {
    if (scancode > 85) {
      kprint_hex(scancode);
    }
    kprint_char(key_map[scancode]);
  }
  outb(0x20, 0x20);
}

void keyboard_init(void) { register_interrupt_handler(33, keyboard_callback); }
