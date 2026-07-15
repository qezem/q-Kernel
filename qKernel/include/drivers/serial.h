#pragma once

#define COM1 0x3f8

int init_serial(void);

void write_serial(char c);
void write_string_serial(const char *str);

char read_serial(void);
