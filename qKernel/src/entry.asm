[bits 16]

global start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

start:
  xor ax, ax
  mov ds, ax
  mov es, ax
  
  cli
  lgdt [GDT_Descriptor]
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  jmp CODE_SEG:start_protected_mode

GDT_Start:
  dq 0x0
GDT_Code:
  dw 0xffff, 0x0 
  db 0x0, 0x9a, 0xcf, 0x0
GDT_Data:
  dw 0xffff, 0x0 
  db 0x0, 0x92, 0xcf, 0x0 
GDT_End:

GDT_Descriptor:
  dw GDT_End - GDT_Start - 1
  dd GDT_Start


[bits 32]

global _start
global gdt_flush

extern kmain

start_protected_mode:
_start:
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov esp, 0x90000

  call kmain

  jmp $

gdt_flush:
  mov eax, [esp + 4]
  lgdt[eax]

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp 0x08:.reload_cs
.reload_cs:
  ret
