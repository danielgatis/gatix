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
#include "load/multiboot.h"

#define K_PMM_STACK_ADDR 0xFF000000

void k_init_pmm(uint32_t start);

uint32_t k_pmm_alloc_page();

void k_pmm_free_page(uint32_t p);

#endif
