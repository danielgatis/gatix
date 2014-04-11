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

#ifndef _tables_idt_h_
#define _tables_idt_h_

#include "types.h"

void k_init_idt();

// lets us access our ASM functions from our C code.
extern void k_idt_flush(uint32_t);

// a struct describing an interrupt gate.
struct idt_entry_struct
{
  uint16_t base_lo;             // the lower 16 bits of the address to jump to when this interrupt fires.
  uint16_t sel;                 // kernel segment selector.
  uint8_t  always0;             // this must always be zero.
  uint8_t  flags;               // more flags. See documentation.
  uint16_t base_hi;             // the upper 16 bits of the address to jump to.
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// a struct describing a pointer to an array of interrupt handlers.
// this is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
  uint16_t limit;
  uint32_t base;                // the address of the first element in our idt_entry_t array.
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

#endif
