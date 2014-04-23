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

#ifndef _arch_idt_h_
#define _arch_idt_h_

#include "std/types.h"

#define IDT_NUM_ENTRIES         256
#define IDT_FLAG_TYPE32TASK     (0x05 << 0)
#define IDT_FLAG_TYPE16INT      (0x06 << 0)
#define IDT_FLAG_TYPE16TRAP     (0x07 << 0)
#define IDT_FLAG_TYPE32INT      (0x0e << 0)
#define IDT_FLAG_TYPE32TRAP     (0x0f << 0)
#define IDT_FLAG_STORAGE        (0x01 << 4)
#define IDT_FLAG_RING0          (0x00 << 5)
#define IDT_FLAG_RING1          (0x01 << 5)
#define IDT_FLAG_RING2          (0x02 << 5)
#define IDT_FLAG_RING3          (0x03 << 5)
#define IDT_FLAG_PRESENT        (0x01 << 7)

typedef struct
{
  uint16_t base_lo;
  uint16_t selector;
  uint8_t  always0;
  uint8_t  flags;
  uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;


typedef struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;


typedef void (*idt_seted_handler)(registers_t *registers);

idt_seted_handler idt_get_handler(uint8_t i);
void idt_set_handler(uint8_t i, idt_seted_handler);
void idt_unset_handler(uint8_t i);

void idt_init();
void idt_add_entry(uint8_t index, void (*callback)(), uint16_t selector, uint8_t flags);

extern void idt_flush(idt_ptr_t *idt_ptr);

#endif
