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

#include "desc/gdt.h"

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

void k_gdt_add_entry(int32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
  gdt_entries[i].base_low = (base & 0xFFFF);
  gdt_entries[i].base_middle = (base >> 16) & 0xFF;
  gdt_entries[i].base_high = (base >> 24) & 0xFF;

  gdt_entries[i].limit_low = (limit & 0xFFFF);
  gdt_entries[i].granularity = (limit >> 16) & 0x0F;

  gdt_entries[i].granularity |= granularity & 0xF0;
  gdt_entries[i].access = access;
}

void k_init_gdt()
{
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
  gdt_ptr.base  = (int32_t)&gdt_entries;

  k_gdt_add_entry(0, 0, 0, 0, 0);
  k_gdt_add_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  k_gdt_add_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  k_gdt_add_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  k_gdt_add_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  k_gdt_flush(&gdt_ptr);
}
