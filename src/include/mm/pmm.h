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

#ifndef _mm_pmm_h_
#define _mm_pmm_h_

#include "std/types.h"

 //! 8 blocks per byte
#define K_PMM_BLOCKS_PER_BYTE 8

//! block size (4k)
#define K_PMM_BLOCK_SIZE 4096

//! block alignment
#define K_PMM_BLOCK_ALIGN  K_PMM_BLOCK_SIZE

void k_init_pmm(uint32_t base, uint32_t size);

void k_pmm_init_region(uint32_t base, uint32_t size);

void k_pmm_set(uint32_t bit);

void k_pmm_unset(uint32_t bit);

int k_pmm_test(uint32_t bit);

int k_pmm_first_free();

int k_mmap_first_free_s(uint32_t size);

#endif
