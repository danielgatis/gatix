[BITS 32]
[GLOBAL k_idt_flush]  ; allows the C code to call idt_flush().

k_idt_flush:
  mov eax, [esp+4]  ; get the pointer to the IDT, passed as a parameter.
  lidt [eax]        ; load the IDT pointer.
  ret
