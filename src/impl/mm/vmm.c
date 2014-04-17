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

// #include "mm/vmm.h"
// #include "mm/pmm.h"
// #include "desc/idt.h"
// #include "std/string.h"
// #include "std/panic.h"
// #include "std/memory.h"
// #include "output/monitor.h"

// uint32_t *page_directory = (uint32_t *)K_PAGE_DIR_VIRTUAL_ADDR;
// uint32_t *page_tables = (uint32_t *)K_PAGE_TABLE_VIRTUAL_ADDR;

// page_directory_t *current_directory;

// extern char pmm_paging_active;

// void k_init_vmm()
// {
//   int i;
//   uint32_t cr0;

//   // Register the page fault handler.
//   k_idt_set_handler(14, k_page_fault_handler);

//   // Create a page directory.
//   page_directory_t *pd = (page_directory_t*)k_pmm_alloc_page();

//   // Initialise it.
//   k_memset((uint8_t*)pd, 0, K_4KB);

//   // Identity map the first 4 MB.
//   pd[0] = k_pmm_alloc_page() | K_PAGE_PRESENT | K_PAGE_WRITE;
//   uint32_t *pt = (uint32_t*) (pd[0] & K_PAGE_MASK);
//   for (i = 0; i < 1024; i++)
//     pt[i] = i * K_4KB | K_PAGE_PRESENT | K_PAGE_WRITE;

//   // Assign the second-last table and zero it.
//   pd[1022] = k_pmm_alloc_page() | K_PAGE_PRESENT | K_PAGE_WRITE;
//   pt = (uint32_t*) (pd[1022] & K_PAGE_MASK);
//   k_memset((uint8_t*)pt, 0, K_4KB);

//   // The last entry of the second-last table is the directory itself.
//   pt[1023] = (uint32_t)pd | K_PAGE_PRESENT | K_PAGE_WRITE;

//   // The last table loops back on the directory itself.
//   pd[1023] = (uint32_t)pd | K_PAGE_PRESENT | K_PAGE_WRITE;

//   // Set the current directory.
//   k_switch_page_directory(pd);

//   // Enable paging.
//   __asm__ __volatile__ ("mov %%cr0, %0" : "=r" (cr0));
//   cr0 |= 0x80000000;
//   __asm__ __volatile__ ("mov %0, %%cr0" : : "r" (cr0));

//   // We need to map the page table where the physical memory manager keeps its page stack
//   // else it will panic on the first "pmm_free_page".
//   uint32_t pt_idx = K_PAGE_DIR_IDX((K_PMM_STACK_ADDR >> 12));
//   page_directory[pt_idx] = k_pmm_alloc_page() | K_PAGE_PRESENT | K_PAGE_WRITE;
//   k_memset((uint8_t*)page_tables[pt_idx * 1024], 0, K_4KB);

//   // Paging is now active. Tell the physical memory manager.
//   pmm_paging_active = 1;

// }

// void k_switch_page_directory(page_directory_t *pd)
// {
//   current_directory = pd;
//   __asm__ __volatile__ ("mov %0, %%cr3" : : "r" (pd));
// }

// void k_map(uint32_t va, uint32_t pa, uint32_t flags)
// {
//   uint32_t virtual_page = va / K_4KB;
//   uint32_t pt_idx = K_PAGE_DIR_IDX(virtual_page);

//   // Find the appropriate page table for 'va'.
//   if (page_directory[pt_idx] == 0)
//   {
//     // The page table holding this page has not been created yet.
//     page_directory[pt_idx] = k_pmm_alloc_page() | K_PAGE_PRESENT | K_PAGE_WRITE;
//     k_memset((uint8_t*)page_tables[pt_idx * 1024], 0, K_4KB);
//   }

//   // Now that the page table definately exists, we can update the PTE.
//   page_tables[virtual_page] = (pa & K_PAGE_MASK) | flags;
// }

// void k_unmap(uint32_t va)
// {
//   uint32_t virtual_page = va / K_4KB;

//   page_tables[virtual_page] = 0;
//   // Inform the CPU that we have invalidated a page mapping.
//   __asm__ __volatile__ ("invlpg (%0)" : : "a" (va));
// }

// char k_get_mapping(uint32_t va, uint32_t *pa)
// {
//   uint32_t virtual_page = va / K_4KB;
//   uint32_t pt_idx = K_PAGE_DIR_IDX(virtual_page);

//   // Find the appropriate page table for 'va'.
//   if (page_directory[pt_idx] == 0)
//     return 0;

//   if (page_tables[virtual_page] != 0)
//   {
//     if (pa) *pa = page_tables[virtual_page] & K_PAGE_MASK;
//     return 1;
//   }
//   // Dummy return.. Will never be reached
//   return -1;
// }

// void k_page_fault_handler(registers_t registers)
// {
//   uint32_t cr2;
//   __asm__ __volatile__ ("mov %%cr2, %0" : "=r" (cr2));

//   // k_monitor_puts_s("Page fault at 0x%x, faulting address 0x%x\n", regs->eip, cr2);
//   // k_monitor_puts_s("Error code: %x\n", regs->err_code);
//   k_panic("Page fault!");
// }
