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

#include "arch/gdt.h"

gdt_entry_t gdt_entries[GDT_NUM_ENTRIES];
gdt_ptr_t gdt_ptr;

uint16_t gdt_add_entry(size_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
  gdt_entries[index].base_low = base & 0xFFFF;
  gdt_entries[index].base_middle = (base >> 16) & 0xFF;
  gdt_entries[index].base_high = (base >> 24) & 0xFF;
  gdt_entries[index].limit_low = limit & 0xFFFF;
  gdt_entries[index].flags = (flags & 0xf0) | ((limit >> 16) & 0x0f);
  gdt_entries[index].access = access;

  return (sizeof(gdt_entry_t) * index) | ((access >> 5) & 0x03);
}

gdt_entries_t gdt_init()
{
  gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_NUM_ENTRIES) - 1;
  gdt_ptr.base  = (int32_t)&gdt_entries;

  gdt_entries_t entries;

  /* null gate */
  gdt_add_entry(0, 0, 0, 0, 0);

  /* kernel mode gates */
  entries.kcode = gdt_add_entry(1, 0x00000000, 0xffffffff, ACCESS_KCODE, GDT_FLAGS);
  entries.kdata = gdt_add_entry(2, 0x00000000, 0xffffffff, ACCESS_KDATA, GDT_FLAGS);

  /* user mode gates */
  entries.ucode = gdt_add_entry(3, 0x00000000, 0xffffffff, ACCESS_UCODE, GDT_FLAGS);
  entries.udata = gdt_add_entry(4, 0x00000000, 0xffffffff, ACCESS_UDATA, GDT_FLAGS);

  gdt_flush(&gdt_ptr);

  return entries;
}
