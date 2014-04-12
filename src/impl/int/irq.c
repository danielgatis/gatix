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

#include "int/irq.h"
#include "std/io.h"
#include "desc/idt.h"

k_irq_seted_handler handlers[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void k_irq_set_handler(uint8_t i, k_irq_seted_handler handler) {
  handlers[i] = handler;
}

void k_irq_unset_handler(uint8_t i) {
  handlers[i] = 0;
}

void k_irq_remap() {
  k_outb(0x20, 0x11);
  k_outb(0xA0, 0x11);
  k_outb(0x21, 0x20);
  k_outb(0xA1, 0x28);
  k_outb(0x21, 0x04);
  k_outb(0xA1, 0x02);
  k_outb(0x21, 0x01);
  k_outb(0xA1, 0x01);
  k_outb(0x21, 0x0);
  k_outb(0xA1, 0x0);
}

void k_init_irq() {
  k_irq_remap();

  k_idt_set_entry(32, (uint32_t)k_irq0 , 0x08, 0x8E);
  // k_idt_set_entry(33, (uint32_t)k_irq1 , 0x08, 0x8E);
  // k_idt_set_entry(34, (uint32_t)k_irq2 , 0x08, 0x8E);
  // k_idt_set_entry(35, (uint32_t)k_irq3 , 0x08, 0x8E);
  // k_idt_set_entry(36, (uint32_t)k_irq4 , 0x08, 0x8E);
  // k_idt_set_entry(37, (uint32_t)k_irq5 , 0x08, 0x8E);
  // k_idt_set_entry(38, (uint32_t)k_irq6 , 0x08, 0x8E);
  // k_idt_set_entry(39, (uint32_t)k_irq7 , 0x08, 0x8E);
  // k_idt_set_entry(40, (uint32_t)k_irq8 , 0x08, 0x8E);
  // k_idt_set_entry(41, (uint32_t)k_irq9 , 0x08, 0x8E);
  // k_idt_set_entry(42, (uint32_t)k_irq10, 0x08, 0x8E);
  // k_idt_set_entry(43, (uint32_t)k_irq11, 0x08, 0x8E);
  // k_idt_set_entry(44, (uint32_t)k_irq12, 0x08, 0x8E);
  // k_idt_set_entry(45, (uint32_t)k_irq13, 0x08, 0x8E);
  // k_idt_set_entry(46, (uint32_t)k_irq14, 0x08, 0x8E);
  // k_idt_set_entry(47, (uint32_t)k_irq15, 0x08, 0x8E);
}

// this gets called from our ASM interrupt handler stub.
void k_irq_handler(registers_t *registers)
{
  k_irq_seted_handler handler = handlers[registers->int_no - 32];

  if (handler) {
    handler(registers);
  }

  if (registers->int_no >= 40) {
    k_outb(0xA0, 0x20);
  }

  k_outb(0x20, 0x20);
}
