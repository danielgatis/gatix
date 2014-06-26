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

#include "mm/heap.h"

static addr_t heap_addr = 0;

static addr_t kmalloc_internal(uint32_t size, bool align, addr_t *phys)
{
  if (align == TRUE && (heap_addr & 0xFFFFF000))
  {
    heap_addr &= 0xFFFFF000;
    heap_addr += KB_4;
  }
 
  if (phys)
  {
    *phys = heap_addr;
  }
 
  addr_t tmp = heap_addr;
  heap_addr += size;
  return tmp;
}

addr_t kmalloc_a(uint32_t size)
{
  return kmalloc_internal(size, 1, 0);
}

addr_t kmalloc_p(uint32_t size, addr_t *phys)
{
  return kmalloc_internal(size, 0, phys);
}

addr_t kmalloc_ap(uint32_t size, addr_t *phys)
{
  return kmalloc_internal(size, 1, phys);
}

addr_t kmalloc(uint32_t size)
{
  return kmalloc_internal(size, 0, 0);
}

addr_t heap_init(addr_t addr) 
{
  heap_addr = addr;
  return heap_addr;
}
