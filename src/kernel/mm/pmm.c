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

#include "init/multiboot.h"

#include "std/types.h"
#include "std/logging.h"
#include "std/string.h"

static uint32_t memory_size;
static uint32_t used_blocks;
static uint32_t max_blocks;

static uint32_t *frames;
static uint32_t last_alloc_block = 0;

static void set_block(uint32_t frame)
{
	frames[frame / 32] |= (1 << (frame % 32));
}

static void clear_block(uint32_t frame)
{
  frames[frame / 32] &= ~(1 << (frame % 32));
}

static int first_block()
{
  uint32_t i, j;
  uint32_t last_frame = last_alloc_block / 32;
  for (i = last_frame; (i - last_frame) < max_blocks; ++i, i %= max_blocks)
  {
    if (frames[i] != 0xffffffff)
    {
      for (j = 0; j < 32; ++j)
      {
        uint32_t bit = 1 << j;
        if (!(frames[i] & bit))
        {
          last_alloc_block = i * 32 + j;
          return last_alloc_block;
        }
      }
    }
  }
  return -1;
}

static void set_region(addr_t base, size_t len)
{
  uint32_t blocks = len / BLOCK_SIZE;
  uint32_t align  = base / BLOCK_SIZE;

  for (; blocks > 0; --blocks, ++align)
  {
    set_block(align);
    ++used_blocks;
  }
}

static void clear_region(addr_t base, size_t len)
{
  uint32_t blocks = len / BLOCK_SIZE;
  uint32_t align  = base / BLOCK_SIZE;

  for (; blocks > 0; --blocks, ++align)
  {
    clear_block(align);
    --used_blocks;
  }

  /* first 4K is always set to protect the IVT, BDA, EBDA, VRAM... */
  set_block(0);
}

void pmm_init(multiboot_info_t* mbi, size_t mem_size, size_t kernel_size)
{
  /* round up kernel size to next BLOCK_SIZE */
  uint32_t ksize = kernel_size;
  if (ksize % BLOCK_SIZE)
  {
    ksize -= (ksize % BLOCK_SIZE);
    ksize += BLOCK_SIZE;
  }

  frames = (uint32_t *)(0x100000 + ksize); /* 1M + kernel_size */;
  memory_size = mem_size;
  max_blocks = memory_size / BLOCK_SIZE;
  used_blocks = max_blocks;

  /* by default, all memory is in use */
  memsetw(frames, 0xffff, max_blocks / 16); /* 16 blocks per word */

  /* free available regions */
  multiboot_memory_map_t * mmap = (multiboot_memory_map_t *)(mbi->mmap_addr);

  while ((uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length)
  {
    if (mmap->type > 4)
      mmap->type = 1;

    if (mmap->type == 1)
    {
      clear_region(mmap->addr_low, mmap->len_low);
    }

    mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
  }

  /* reserve blocks for kernel and frames */
  uint32_t msize = mem_size / BLOCK_SIZE / 8;
  if (msize % BLOCK_SIZE) {
    msize -= (msize % BLOCK_SIZE);
    msize += BLOCK_SIZE;
  }
  set_region(0x100000, ksize + msize);

  kprintf(DEBUG, "[pmm] %u blocks of %uKB - %u used - %u free\n",
    max_blocks, (BLOCK_SIZE / 1024), used_blocks, pmm_num_free_blocks());
}

addr_t pmm_alloc_block()
{
  int frame;
  if ((pmm_num_free_blocks() == 0) || ((frame = first_block()) == -1))
    return 0;

  set_block(frame);

  ++used_blocks;
  return (addr_t)(frame * BLOCK_SIZE);
}

void pmm_free_block(addr_t addr)
{
  clear_block(addr / BLOCK_SIZE);
  --used_blocks;
}

uint32_t pmm_num_free_blocks()
{
  return max_blocks - used_blocks;
}

uint32_t pmm_num_used_blocks()
{
  return used_blocks;
}

uint32_t pmm_memory_size()
{
  return memory_size;
}
