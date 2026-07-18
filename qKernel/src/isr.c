#include "isr.h"
#include "drivers/vga.h"
#include "kernel.h"
#include "libs/io.h"
#include "libs/stdio.h"
#include <stdint.h>

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t num, isr_t handler) {
  interrupt_handlers[num] = handler;
}

void isr_handler(struct registers *regs) {
  if (regs->int_no == 0) {
    kernel_panic("KERNEL PANIC! Division by zero!");
  }
  kprint_int(regs->int_no);
}

void irq_handler(struct registers *regs) {
  if (interrupt_handlers[regs->int_no] != 0) {
    isr_t handler = interrupt_handlers[regs->int_no];
    handler(regs);
  }

  outb(0x20, 0x20);
  if (regs->int_no < 40) {
    outb(0xa0, 0x20);
  }
}
