GDT_Start:
  null_descriptor:
    dd 0
    dd 0
  code_descriptor:
    dw 0xffff ; first 16 bits of the limit
    dw 0 ; first 16 bits of the base
    db 0 ; next 8 bits of the base
    db 10011010b ; type flags
    db 11001111b ; other flags
    db 0 ; last 8 bits of the base
  data_descriptor:
    dw 0xffff
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0

GDT_End:

GDT_Descriptor:
  dw GDT_End - GDT_Start - 1 ; size
  dd GDT_Start ; start

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start
; set constans
