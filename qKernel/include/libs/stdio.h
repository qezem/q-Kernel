#pragma once

#include "drivers/vga.h"
#include <stdint.h>

#define EOF (-1)

int printf(const char *format, ...);
int puts(const char *str);
int putchar(int character);
