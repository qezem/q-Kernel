[bits 16]
[org 0x0000]

start:
  mov ax, cs
  mov ds, ax
  mov es, ax

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

msg: db 'Kernel is ready!', 0x0d, 0x0a, 0

times 512-($-$$) db 0
