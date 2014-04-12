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

#include "int/isr.h"
#include "output/monitor.h"
#include "desc/idt.h"

char *exception_messages[] =
{
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",

  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",

  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",

  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

void k_init_isr() {
  k_idt_set_entry( 0, (uint32_t)k_isr0 , 0x08, 0x8E);
  k_idt_set_entry( 1, (uint32_t)k_isr1 , 0x08, 0x8E);
  k_idt_set_entry( 2, (uint32_t)k_isr2 , 0x08, 0x8E);
  k_idt_set_entry( 3, (uint32_t)k_isr3 , 0x08, 0x8E);
  k_idt_set_entry( 4, (uint32_t)k_isr4 , 0x08, 0x8E);
  k_idt_set_entry( 5, (uint32_t)k_isr5 , 0x08, 0x8E);
  k_idt_set_entry( 6, (uint32_t)k_isr6 , 0x08, 0x8E);
  k_idt_set_entry( 7, (uint32_t)k_isr7 , 0x08, 0x8E);
  k_idt_set_entry( 8, (uint32_t)k_isr8 , 0x08, 0x8E);
  k_idt_set_entry( 9, (uint32_t)k_isr9 , 0x08, 0x8E);
  k_idt_set_entry(10, (uint32_t)k_isr10, 0x08, 0x8E);
  k_idt_set_entry(11, (uint32_t)k_isr11, 0x08, 0x8E);
  k_idt_set_entry(12, (uint32_t)k_isr12, 0x08, 0x8E);
  k_idt_set_entry(13, (uint32_t)k_isr13, 0x08, 0x8E);
  k_idt_set_entry(14, (uint32_t)k_isr14, 0x08, 0x8E);
  k_idt_set_entry(15, (uint32_t)k_isr15, 0x08, 0x8E);
  k_idt_set_entry(16, (uint32_t)k_isr16, 0x08, 0x8E);
  k_idt_set_entry(17, (uint32_t)k_isr17, 0x08, 0x8E);
  k_idt_set_entry(18, (uint32_t)k_isr18, 0x08, 0x8E);
  k_idt_set_entry(19, (uint32_t)k_isr19, 0x08, 0x8E);
  k_idt_set_entry(20, (uint32_t)k_isr20, 0x08, 0x8E);
  k_idt_set_entry(21, (uint32_t)k_isr21, 0x08, 0x8E);
  k_idt_set_entry(22, (uint32_t)k_isr22, 0x08, 0x8E);
  k_idt_set_entry(23, (uint32_t)k_isr23, 0x08, 0x8E);
  k_idt_set_entry(24, (uint32_t)k_isr24, 0x08, 0x8E);
  k_idt_set_entry(25, (uint32_t)k_isr25, 0x08, 0x8E);
  k_idt_set_entry(26, (uint32_t)k_isr26, 0x08, 0x8E);
  k_idt_set_entry(27, (uint32_t)k_isr27, 0x08, 0x8E);
  k_idt_set_entry(28, (uint32_t)k_isr28, 0x08, 0x8E);
  k_idt_set_entry(29, (uint32_t)k_isr29, 0x08, 0x8E);
  k_idt_set_entry(30, (uint32_t)k_isr30, 0x08, 0x8E);
  k_idt_set_entry(31, (uint32_t)k_isr31, 0x08, 0x8E);
}

// this gets called from our ASM interrupt handler stub.
void k_isr_handler(registers_t *registers)
{
  if (registers->int_no < 32)
  {
    k_monitor_puts_s(exception_messages[registers->int_no]);
    k_monitor_puts_s("Exception. System Halted!");

    __asm__ __volatile__ ("cli");
    __asm__ __volatile__ ("hlt");
  }
}
