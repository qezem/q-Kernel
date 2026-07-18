#pragma once

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TEXT_COLOR 0x0f

void clear_buffer(void);

void kprint_char(char c);
void kprint_hex(unsigned char hex);
int kprint_int(int num);
int kprint_string(const char *str);
