#include "libs/stdio/stdio.h"

void kmain(void) {
  printf("Kernel is working!\n", 0x0f);
  printf("VGA driver is working!\n", 0x0c);
  printf("%d %d %c %s", 6, 7, 'a', "Hello ");
}
