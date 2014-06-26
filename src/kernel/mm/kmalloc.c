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

#include "mm/kmalloc.h"

static addr_t placement_addr = 0;

static addr_t kmalloc_internal(uint32_t size, bool align, addr_t *phys)
{
  if (align == TRUE && (placement_addr & 0xFFFFF000))
  {
    placement_addr &= 0xFFFFF000;
    placement_addr += KB_4;
  }
 
  if (phys)
  {
    *phys = placement_addr;
  }
 
  addr_t tmp = placement_addr;
  placement_addr += size;
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

addr_t kmalloc_init(addr_t addr) 
{
  placement_addr = addr;
  return placement_addr;
}
