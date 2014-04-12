[BITS 32]

extern gdt_ptr
global k_gdt_flush
k_gdt_flush:
  lgdt [gdt_ptr]
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:.flush

.flush:
  ret
