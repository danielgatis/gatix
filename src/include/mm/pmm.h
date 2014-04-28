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

#ifndef _mm_pmm_h
#define _mm_pmm_h

#include "init/multiboot.h"
#include "std/types.h"

#define BLOCK_SIZE 0x1000

void pmm_init(multiboot_info_t* mbi, size_t mem_size, size_t kernel_size);

addr_t pmm_alloc_block();
void pmm_free_block(addr_t addr);

uint32_t pmm_num_free_blocks();
uint32_t pmm_num_used_blocks();
uint32_t pmm_memory_size();

#endif
