#include "isr.h"
#include "drivers/vga.h"
#include "kernel.h"
#include "libs/stdio.h"

void isr_handler(struct registers *regs) {
  if (regs->int_no == 0) {
    kernel_panic("KERNEL PANIC! Division by zero!");
  }
  kprint_int(regs->int_no);
}
