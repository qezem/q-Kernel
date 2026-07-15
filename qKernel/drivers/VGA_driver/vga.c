#include "vga.h"
#include "../../libs/io.h"
#include <stdint.h>

static char *video_mem = (char *)0xb8000;

static int cursor = 0;

void move_to_the_next_line(void) {
  cursor = (cursor / (VGA_WIDTH * 2) + 1) * VGA_WIDTH * 2;
}

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
    video_mem[cursor + 1] = TEXT_COLOR;
    cursor += 2;
  }

  if (cursor >= VGA_HEIGHT * VGA_WIDTH * 2) {
    scroll_screen();
  }

  update_cursor();
}

int kprint_int(int num) {
  int count = 0;

  if (num == 0) {
    kprint_char('0');
    update_cursor();

    return 1;
  }

  char buffer[12];
  int i = 0;

  unsigned int abs_num = num;

  if (num < 0) {
    kprint_char('-');
    ++count;
    abs_num = -num;
  }

  while (abs_num > 0) {
    buffer[i++] = (abs_num % 10) + '0';
    abs_num = abs_num / 10;
  }

  while (i > 0) {
    kprint_char(buffer[--i]);
    ++count;
  }

  update_cursor();

  return count;
}

int kprint_string(const char *str) {
  int count = 0;

  for (int i = 0; str[i] != '\0'; ++i) {
    kprint_char(str[i]);
    ++count;
  }

  return count;
}
