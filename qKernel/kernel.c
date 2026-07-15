#include "libs/stdio/stdio.h"

void kmain(void) {
  printf("Kernel is working!\n");
  printf("VGA driver is working!\n");
  printf("%d %d %c %s", 6, 7, 'c', "String");
  puts("puts");
  putchar(1);
}
