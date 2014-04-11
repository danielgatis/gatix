/*
 * Gatix
 * Copyright (C) 2014  Daniel Gatis Carrazzoni
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "types.h"
#include "memory.h"
#include "tables/idt.h"

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void k_isr0();
extern void k_isr1();
extern void k_isr2();
extern void k_isr3();
extern void k_isr4();
extern void k_isr5();
extern void k_isr6();
extern void k_isr7();
extern void k_isr8();
extern void k_isr9();
extern void k_isr10();
extern void k_isr11();
extern void k_isr12();
extern void k_isr13();
extern void k_isr14();
extern void k_isr15();
extern void k_isr16();
extern void k_isr17();
extern void k_isr18();
extern void k_isr19();
extern void k_isr20();
extern void k_isr21();
extern void k_isr22();
extern void k_isr23();
extern void k_isr24();
extern void k_isr25();
extern void k_isr26();
extern void k_isr27();
extern void k_isr28();
extern void k_isr29();
extern void k_isr30();
extern void k_isr31();

static void k_idt_set_gate(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt_entries[i].base_lo = base & 0xFFFF;
  idt_entries[i].base_hi = (base >> 16) & 0xFFFF;

  idt_entries[i].sel = sel;
  idt_entries[i].always0 = 0;
  // we must uncomment the OR below when we get to using user-mode.
  // it sets the interrupt gate's privilege level to 3.
  idt_entries[i].flags = flags /* | 0x60 */;
}

void k_init_idt()
{
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base  = (uint32_t)&idt_entries;

  k_memset((uint8_t*)&idt_entries, 0, sizeof(idt_entry_t) * 256);

  k_idt_set_gate( 0, (uint32_t)k_isr0 , 0x08, 0x8E);
  k_idt_set_gate( 1, (uint32_t)k_isr1 , 0x08, 0x8E);
  k_idt_set_gate( 2, (uint32_t)k_isr2 , 0x08, 0x8E);
  k_idt_set_gate( 3, (uint32_t)k_isr3 , 0x08, 0x8E);
  k_idt_set_gate( 4, (uint32_t)k_isr4 , 0x08, 0x8E);
  k_idt_set_gate( 5, (uint32_t)k_isr5 , 0x08, 0x8E);
  k_idt_set_gate( 6, (uint32_t)k_isr6 , 0x08, 0x8E);
  k_idt_set_gate( 7, (uint32_t)k_isr7 , 0x08, 0x8E);
  k_idt_set_gate( 8, (uint32_t)k_isr8 , 0x08, 0x8E);
  k_idt_set_gate( 9, (uint32_t)k_isr9 , 0x08, 0x8E);
  k_idt_set_gate(10, (uint32_t)k_isr10, 0x08, 0x8E);
  k_idt_set_gate(11, (uint32_t)k_isr11, 0x08, 0x8E);
  k_idt_set_gate(12, (uint32_t)k_isr12, 0x08, 0x8E);
  k_idt_set_gate(13, (uint32_t)k_isr13, 0x08, 0x8E);
  k_idt_set_gate(14, (uint32_t)k_isr14, 0x08, 0x8E);
  k_idt_set_gate(15, (uint32_t)k_isr15, 0x08, 0x8E);
  k_idt_set_gate(16, (uint32_t)k_isr16, 0x08, 0x8E);
  k_idt_set_gate(17, (uint32_t)k_isr17, 0x08, 0x8E);
  k_idt_set_gate(18, (uint32_t)k_isr18, 0x08, 0x8E);
  k_idt_set_gate(19, (uint32_t)k_isr19, 0x08, 0x8E);
  k_idt_set_gate(20, (uint32_t)k_isr20, 0x08, 0x8E);
  k_idt_set_gate(21, (uint32_t)k_isr21, 0x08, 0x8E);
  k_idt_set_gate(22, (uint32_t)k_isr22, 0x08, 0x8E);
  k_idt_set_gate(23, (uint32_t)k_isr23, 0x08, 0x8E);
  k_idt_set_gate(24, (uint32_t)k_isr24, 0x08, 0x8E);
  k_idt_set_gate(25, (uint32_t)k_isr25, 0x08, 0x8E);
  k_idt_set_gate(26, (uint32_t)k_isr26, 0x08, 0x8E);
  k_idt_set_gate(27, (uint32_t)k_isr27, 0x08, 0x8E);
  k_idt_set_gate(28, (uint32_t)k_isr28, 0x08, 0x8E);
  k_idt_set_gate(29, (uint32_t)k_isr29, 0x08, 0x8E);
  k_idt_set_gate(30, (uint32_t)k_isr30, 0x08, 0x8E);
  k_idt_set_gate(31, (uint32_t)k_isr31, 0x08, 0x8E);

  k_idt_flush((uint32_t)&idt_ptr);
}
