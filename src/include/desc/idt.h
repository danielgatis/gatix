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

#ifndef _desc_idt_h_
#define _desc_idt_h_

#include "std/types.h"

struct idt_entry_struct
{
  uint16_t base_lo;
  uint16_t sel;
  uint8_t  always0;
  uint8_t  flags;
  uint16_t base_hi;
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

void k_init_idt();

void k_idt_add_entry(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags);

extern void k_idt_flush(idt_ptr_t *idt_ptr);

#endif
