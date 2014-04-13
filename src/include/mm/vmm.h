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

#ifndef _mm_vmm_h_
#define _mm_vmm_h_

#include "std/types.h"

#define K_PAGE_DIR_VIRTUAL_ADDR 0xFFBFF000
#define K_PAGE_TABLE_VIRTUAL_ADDR 0xFFC00000
#define K_PAGE_DIR_IDX(x) ((uint32_t) x / 1024)
#define K_PAGE_TABLE_IDX(x) ((uint32_t) x % 1024)

#define K_PAGE_PRESENT 0x1
#define K_PAGE_WRITE 0x2
#define K_PAGE_USER 0x4
#define K_PAGE_MASK 0xFFFFF000

typedef uint32_t page_directory_t;

// Sets up the environment, page directories etc and enables paging.
void k_init_vmm();

// Changes address space.
void k_switch_page_directory (page_directory_t *pd);

// Maps the physical page "pa" into the virtual space at address "va", using
// page protection flags "flags".
void k_map(uint32_t va, uint32_t pa, uint32_t flags);

// Removes one page of V->P mappings at virtual address "va".
void k_unmap(uint32_t va);

// Returns 1 if the given virtual address is mapped in the address space.
// If "*pa" is non-NULL, the physical address of the mapping is placed in *pa.
char k_get_mapping(uint32_t va, uint32_t *pa);

void k_page_fault_handler(registers_t registers);

#endif
