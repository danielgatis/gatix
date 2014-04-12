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

#ifndef _desc_gdt_h_
#define _desc_gdt_h_

#include "std/types.h"

void k_init_gdt();

// lets us access our ASM functions from our C code.
extern void k_gdt_flush();

// this structure contains the value of one GDT entry.
struct gdt_entry_struct
{
  uint16_t limit_low;           // the lower 16 bits of the limit.
  uint16_t base_low;            // the lower 16 bits of the base.
  uint8_t  base_middle;         // the next 8 bits of the base.
  uint8_t  access;              // access flags, determine what ring this segment can be used in.
  uint8_t  granularity;
  uint8_t  base_high;           // the last 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

// this struct describes a GDT pointer. It points to the start of
// our array of GDT entries, and is in the format required by the
// lgdt instruction.
struct gdt_ptr_struct
{
  uint16_t limit;               // the upper 16 bits of all selector limits.
  uint32_t base;                // the address of the first gdt_entry_t struct.
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

void k_gdt_set_entry(int32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif
