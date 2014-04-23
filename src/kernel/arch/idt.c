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

#include "arch/idt.h"
#include "io/vga.h"
#include "std/string.h"

idt_entry_t idt[IDT_NUM_ENTRIES];
idt_ptr_t idt_ptr;
idt_seted_handler handlers[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void idt_set_handler(uint8_t i, idt_seted_handler handler)
{
  handlers[i] = handler;
}

idt_seted_handler idt_get_handler(uint8_t i)
{
  return handlers[i];
}

void idt_unset_handler(uint8_t i)
{
  handlers[i] = 0;
}

void idt_add_entry(uint8_t index, void (*callback)(), uint16_t selector, uint8_t flags)
{
  uint32_t base = (uint32_t)callback;

  idt[index].base_lo = base & 0xFFFF;
  idt[index].base_hi = (base >> 16) & 0xFFFF;

  idt[index].selector = selector;
  idt[index].always0 = 0;
  idt[index].flags = flags;
}

void idt_init()
{
  idt_ptr.limit = sizeof(idt_entry_t) * IDT_NUM_ENTRIES - 1;
  idt_ptr.base = (uint32_t)&idt;
  memset((void *)&idt, 0, sizeof(idt_entry_t) * IDT_NUM_ENTRIES);
  idt_flush(&idt_ptr);
}
