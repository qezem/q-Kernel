#include "vga.h"
#include "../../libs/io.h"
#include <stdint.h>

const uint8_t VGA_WIDTH = 80;
const uint8_t VGA_HEIGHT = 25;

static int cursor = 0;

void move_to_the_next_line(void) { cursor = (cursor / (80 * 2) + 1) * 80 * 2; }

void update_cursor(void) {
  int pos = cursor / 2;
  outb(0x3d4, 0x0f);
  outb(0x3d5, (uint8_t)(pos & 0xff));
  outb(0x3d4, 0x0e);
  outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
}

void scroll_screen(void) {
  char *video_mem = (char *)0xb8000;

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

void kprint(const char *str, unsigned char color) {
  char *video_mem = (char *)0xb8000;

  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == '\n') {
      move_to_the_next_line();
    } else {
      video_mem[cursor] = str[i];
      video_mem[cursor + 1] = color;
      cursor += 2;
    }

    if (cursor >= VGA_HEIGHT * VGA_WIDTH * 2) {
      scroll_screen();
    }
  }

  update_cursor();
}
