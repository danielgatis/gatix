[BITS 32]

extern idt_ptr
global k_idt_flush
k_idt_flush:
  lidt [idt_ptr]
  ret
