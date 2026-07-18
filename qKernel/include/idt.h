#pragma once

#include <stdint.h>

typedef enum { IDT_SUCCESS, IDT_ERR_PTR_INVALID } idt_status;

struct idt_entry {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t type_attr;
  uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

idt_status idt_init(void);
