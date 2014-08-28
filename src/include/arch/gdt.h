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

#ifndef _arch_gdt_h_
#define _arch_gdt_h_

#include "std/types.h"

#define GDT_NUM_ENTRIES         5
#define GDT_ACCESS_ACCESSED     (0x01 << 0) /* accessed bit (set to 0, the cpu sets this to 1 when the segment is accessed) */
#define GDT_ACCESS_RW           (0x01 << 1) /* readable bit for code selector, writable bit for data selector */
#define GDT_ACCESS_DC           (0x01 << 2) /* direction/conforming bit */
#define GDT_ACCESS_EXECUTE      (0x01 << 3) /* executable bit (1 for code selector, 0 for data selector) */
#define GDT_ACCESS_ALWAYS1      (0x01 << 4) /* descriptor type (0 for system, 1 for code/data) */
#define GDT_ACCESS_RING0        (0x00 << 5)
#define GDT_ACCESS_RING1        (0x01 << 5)
#define GDT_ACCESS_RING2        (0x02 << 5)
#define GDT_ACCESS_RING3        (0x03 << 5)
#define GDT_ACCESS_PRESENT      (0x01 << 7)

#define GDT_FLAG_32BIT          (0x01 << 6) /* operation size (0 for 16 bit, 1 for 32) */
#define GDT_FLAG_GRANULARITY    (0x01 << 7) /* granularity (0 for 1B-1MB, 1 for 4KB-4GB) */

#define ACCESS_KCODE (GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_ALWAYS1 | GDT_ACCESS_RW | GDT_ACCESS_EXECUTE)
#define ACCESS_KDATA (GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_ALWAYS1 | GDT_ACCESS_RW)

#define ACCESS_UCODE (GDT_ACCESS_PRESENT | GDT_ACCESS_RING3 | GDT_ACCESS_ALWAYS1 | GDT_ACCESS_RW | GDT_ACCESS_EXECUTE)
#define ACCESS_UDATA (GDT_ACCESS_PRESENT | GDT_ACCESS_RING3 | GDT_ACCESS_ALWAYS1 | GDT_ACCESS_RW)

#define GDT_FLAGS    (GDT_FLAG_GRANULARITY | GDT_FLAG_32BIT)

typedef struct
{
  uint16_t kcode;
  uint16_t ucode;
  uint16_t kdata;
  uint16_t udata;
} gdt_entries_t;

typedef struct
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  flags;
  uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

gdt_entries_t gdt_init();
uint16_t gdt_add_entry(size_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
extern void gdt_flush(gdt_ptr_t *gdt_ptr);

#endif
