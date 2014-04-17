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

#include "mm/pmm.h"
#include "std/memory.h"

//! size of physical memory
static  uint32_t  k_pmm_memory_size = 0;

//! maximum number of available memory blocks
static  uint32_t  k_pmm_max_blocks = 0;

//! memory map bit array. Each bit represents a memory block
static  uint32_t* k_pmm_memory_map = 0;

void k_init_pmm(uint32_t base, uint32_t size)
{
  k_pmm_memory_size  = size;
  k_pmm_memory_map = (uint32_t*) base;
  k_pmm_max_blocks = (k_pmm_memory_size * 1024) / K_PMM_BLOCK_SIZE;

  k_memset(k_pmm_memory_map, 0x0, k_pmm_max_blocks / K_PMM_BLOCKS_PER_BYTE);
}

void k_pmm_set(uint32_t bit)
{
  k_pmm_memory_map[bit / 32] |= (1 << (bit % 32));
}

void k_pmm_unset(uint32_t bit)
{
  k_pmm_memory_map[bit / 32] &= ~ (1 << (bit % 32));
}

int k_pmm_test(uint32_t bit)
{
  return k_pmm_memory_map[bit / 32] & (1 << (bit % 32));
}

int k_pmm_first_free()
{
  for (uint32_t i = 0; i < k_pmm_max_blocks / 32; i++)
  {
    if (k_pmm_memory_map[i] != 0xffffffff)
    {
      for (int j = 0; j < 32; j++)
      {
        int32_t bit = 1 << j;

        if (! (k_pmm_memory_map[i] & bit) )
        {
          return i * 4 * 8 + j;
        }
      }
    }
  }

  return -1;
}

int k_mmap_first_free_s(uint32_t size) {
  if (size == 0) return -1;
  if (size == 1 ) return k_pmm_first_free();

  for (uint32_t i = 0; i< k_pmm_max_blocks / 32; i++)
  {
    if (k_pmm_memory_map[i] != 0xffffffff)
    {
      for (int j = 0; j < 32; j++)
      {
        int32_t bit = 1 << j;
        if (! (k_pmm_memory_map[i] & bit) )
        {
          int startingBit = i * 32;
          startingBit += bit;

          uint32_t free = 0;
          for (uint32_t count = 0; count <= size; count++)
          {
            if (! k_pmm_test(startingBit + count) ) free++;
            if (free == size) return i * 4 * 8+ j;
          }
        }
      }
    }
  }

  return -1;
}
