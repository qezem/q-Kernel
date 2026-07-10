#include "drivers/VGA_driver/vga.h"

void kmain(void) {
  kprint("Kernel is working!\n", 0x0f);
  kprint("VGA driver is working!", 0x0c);
}
