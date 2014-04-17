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

#include "desc/idt.h"
#include "std/memory.h"
#include "output/monitor.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;
k_idt_seted_handler handlers[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void k_idt_set_handler(uint8_t i, k_idt_seted_handler handler)
{
  handlers[i] = handler;
}

k_idt_seted_handler k_idt_get_handler(uint8_t i)
{
  return handlers[i];
}

void k_idt_unset_handler(uint8_t i)
{
  handlers[i] = 0;
}

void k_idt_add_entry(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt[i].base_lo = base & 0xFFFF;
  idt[i].base_hi = (base >> 16) & 0xFFFF;

  idt[i].sel = sel;
  idt[i].always0 = 0;
  idt[i].flags = flags;
}

void k_init_idt()
{
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = (uint32_t)&idt;
  k_memset((uint32_t*)&idt, 0, sizeof(idt_entry_t) * 256);
  k_idt_flush(&idt_ptr);
}
