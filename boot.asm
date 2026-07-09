[bits 16]
[org 0x7c00]

start:
  cli
  xor ax, ax
  mov ds, ax
  mov es, ax
  mov ss, ax
  mov sp, ax
  sti

  mov ax, 0x0003
  int 0x10

  mov si, msg
  call print

  jmp $

print:
  lodsb
  
  cmp al, 0
  je .done

  mov ah, 0x0e
  int 0x10

  jmp print
.done:
  ret 

msg: db 'Hello', 0x0d, 0x0a, 0

times 510-($-$$) db 0
dw 0xaa55
