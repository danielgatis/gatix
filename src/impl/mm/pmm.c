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
#include "mm/vmm.h"
#include "std/types.h"
#include "std/panic.h"

uint32_t pmm_stack_loc = K_PMM_STACK_ADDR;
uint32_t pmm_stack_max = K_PMM_STACK_ADDR;
uint32_t pmm_location = 0;
char pmm_paging_active = 0;

void k_init_pmm(uint32_t start)
{
  // Ensure the initial page allocation location is page-aligned.
  pmm_location = (start + K_4KB) & K_PAGE_MASK;
}

uint32_t k_pmm_alloc_page()
{
  if (pmm_paging_active)
  {
    // Quick sanity check.
    if (pmm_stack_loc == K_PMM_STACK_ADDR)
      k_panic("Error: out of memory.");

    // Pop off the stack.
    pmm_stack_loc -= sizeof(uint32_t);
    uint32_t *stack = (uint32_t*)pmm_stack_loc;

    return *stack;
  }
  else
  {
    return pmm_location += K_4KB;
  }
}

void k_pmm_free_page(uint32_t p)
{
  // Ignore any page under "location", as it may contain important data initialised
  // at boot (like paging structures!)
  if (p < pmm_location) return;

  // If we've run out of space on the stack...
  if (pmm_stack_max <= pmm_stack_loc)
  {
    // Map the page we're currently freeing at the top of the free page stack.
    k_map(pmm_stack_max, p, K_PAGE_PRESENT | K_PAGE_WRITE);
    // Increase the free page stack's size by one page.
    pmm_stack_max += 4096;
  }
  else
  {
    // Else we have space on the stack, so push.
    uint32_t *stack = (uint32_t*)pmm_stack_loc;
    *stack = p;
    pmm_stack_loc += sizeof(uint32_t);
  }
}
