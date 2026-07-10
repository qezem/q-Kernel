#include "vga.h"
#include "../../libs/io.h"
#include <stdint.h>

static char *video_mem = (char *)0xb8000;

static int cursor = 0;

const uint8_t VGA_WIDTH = 80;
const uint8_t VGA_HEIGHT = 25;

const unsigned char text_color = 0x0f;

void move_to_the_next_line(void) { cursor = (cursor / (80 * 2) + 1) * 80 * 2; }

void update_cursor(void) {
  int pos = cursor / 2;
  outb(0x3d4, 0x0f);
  outb(0x3d5, (uint8_t)(pos & 0xff));
  outb(0x3d4, 0x0e);
  outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
}

void scroll_screen(void) {
  for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH * 2; ++i) {
    video_mem[i] = video_mem[i + VGA_WIDTH * 2];
  }

  for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i < VGA_HEIGHT * VGA_WIDTH * 2;
       i += 2) {
    video_mem[i] = ' ';
    video_mem[i + 1] = 0x07;
  }

  cursor = (VGA_HEIGHT - 1) * VGA_WIDTH * 2;
}

void kprint_char(char c) {
  if (c == '\n') {
    move_to_the_next_line();
  } else {
    video_mem[cursor] = c;
    video_mem[cursor + 1] = text_color;
    cursor += 2;
  }

  if (cursor >= VGA_HEIGHT * VGA_WIDTH * 2) {
    scroll_screen();
  }

  update_cursor();
}

void kprint_int(int num) {
  if (num == 0) {
    kprint_char('0');
  }

  char buffer[12];
  int i = 0;

  while (num > 0) {
    buffer[i++] = (num % 10) + '0';
    num = num / 10;
  }

  while (i > 0) {
    kprint_char(buffer[--i]);
  }

  update_cursor();
}

void kprint_string(const char *str) {
  for (int i = 0; str[i] != '\0'; ++i) {
    kprint_char(str[i]);
  }
}
