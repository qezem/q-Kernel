#pragma once

#include <stdint.h>

struct registers {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp_dummy, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

typedef void (*isr_t)(struct registers *regs);

void isr_handler(struct registers *regs);
void irq_handler(struct registers *regs);
void register_interrupt_handler(uint8_t num, isr_t handler);
