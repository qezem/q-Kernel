[bits 16]
[org 0x8000]

start:
  xor ax, ax
  mov ds, ax
  mov es, ax

  mov si, msg
  call print
  
  cli
  lgdt [ds:GDT_Descriptor]
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  jmp CODE_SEG:start_protected_mode

print:
  lodsb

  cmp al, 0
  je .done

  mov ah, 0x0e
  int 0x10

  jmp print
.done:
  ret

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

  mov al, 'A'
  mov ah, 0x0f

  mov [0xb8000], ax

  jmp $

msg: db 'Kernel is ready!', 0x0d, 0x0a, 0

times 512-($-$$) db 0
