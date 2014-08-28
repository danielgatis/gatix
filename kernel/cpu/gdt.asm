bits 32

global gdt_flush

KERNEL_CS_OFFSET equ 0x08
KERNEL_DS_OFFSET equ 0x10

gdt_flush:
  mov eax, [esp+4]
  lgdt [eax]
  jmp KERNEL_CS_OFFSET:.flush

.flush:
  mov ax, KERNEL_DS_OFFSET
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  ret
