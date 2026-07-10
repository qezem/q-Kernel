[bits 16]

global start

start:
  xor ax, ax
  mov ds, ax
  mov es, ax
  
  cli
  lgdt [ds:GDT_Descriptor]
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  jmp CODE_SEG:start_protected_mode

%include "gdt.asm"

[bits 32]
start_protected_mode:
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov esp, 0x9000
 
  cld
  mov edi, 0xb8000
  mov ax, 0x0720
  mov ecx, 2000
  rep stosw

  extern kmain
  call kmain

  jmp $


times 512-($-$$) db 0
