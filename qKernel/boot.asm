[bits 16]
[org 0x7c00]

start:
  cli
  xor ax, ax
  mov ds, ax
  mov es, ax
  mov ss, ax
  mov sp, 0x7c00
  sti

  mov ax, 0x0003
  int 0x10

  mov si, msg
  call print

  call load

  jmp $

load:
  mov ax, 0x0800
  mov es, ax
  mov bx, 0x0000

  mov ah, 0x02
  mov al, 0x02
  mov ch, 0x00
  mov cl, 0x02
  mov dh, 0x00

  int 0x13 

  jc .err

  jmp 0x0800:0x0000
.err:
  mov si, err
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
err: db 'Error starting kernel'

times 510-($-$$) db 0
dw 0xaa55
