#include "gdt.h"
#include <stdint.h>

struct gdt_entry gdt_entries[3];
struct gdt_ptr gdt_ptr;

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran) {
  gdt_entries[num].base_low = (base & 0xffff);
  gdt_entries[num].base_mid = (base >> 16) & 0xff;
  gdt_entries[num].base_high = (base >> 24) & 0xff;

  gdt_entries[num].limit_low = (limit & 0xffff);

  gdt_entries[num].granularity = (limit >> 16) & 0x0f;
  gdt_entries[num].granularity |= (gran & 0xf0);

  gdt_entries[num].access = access;
}

int gdt_init(void) {
  gdt_ptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gdt_ptr.base = (uint32_t)&gdt_entries;

  if (gdt_ptr.base == 0) {
    return 1;
  }

  gdt_set_gate(0, 0, 0, 0, 0);

  gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf);

  gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf);

  gdt_flush((uint32_t)&gdt_ptr);

  return 0;
};
