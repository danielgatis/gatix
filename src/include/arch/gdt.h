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

struct gdt_entry_struct
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

void k_init_gdt();

void k_gdt_add_entry(int32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

extern void k_gdt_flush(gdt_ptr_t *gdt_ptr);

#endif
