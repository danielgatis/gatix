[BITS 32]

global k_idt_flush
k_idt_flush:
  mov eax, [esp+4]
  lidt [eax]
  ret
