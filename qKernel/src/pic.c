#include "pic.h"
#include "kernel.h"
#include "libs/io.h"

void pic_remap(int offset1, int offset2) {
  outb(PIC1_COMMAND, 0x11);
  outb(PIC2_COMMAND, 0x11);

  outb(PIC1_DATA, offset1);
  outb(PIC2_DATA, offset2);

  outb(PIC1_DATA, 4);
  outb(PIC2_DATA, 2);

  outb(PIC1_DATA, 0x01);
  outb(PIC2_DATA, 0x01);

  outb(PIC1_DATA, 0);
  outb(PIC2_DATA, 0);
}

void pic_check(void) {
  outb(PIC1_DATA, 0xff);
  if (inb(PIC1_DATA) != 0xff) {
    kernel_panic("KERNEL PANIC! PIC Master verification failed!");
  }

  outb(PIC2_DATA, 0xff);
  if (inb(PIC2_DATA) != 0xff) {
    kernel_panic("KERNEL PANIC! PIC Slave verification failed!");
  }

  outb(PIC1_DATA, 0);
  outb(PIC2_DATA, 0);
}

void pic_init(void) {
  pic_remap(32, 40);
  pic_check();
}
