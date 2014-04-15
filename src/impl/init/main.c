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

#include "std/elf.h"
#include "load/multiboot.h"
#include "output/monitor.h"
#include "input/keyboard.h"
#include "desc/gdt.h"
#include "desc/idt.h"
#include "int/isr.h"
#include "int/irq.h"
#include "sys/pit.h"
#include "mm/vmm.h"
#include "mm/pmm.h"
#include "mm/heap.h"

elf_t kernel_elf;

int k_main(multiboot_info_t *mboot_ptr)
{
  kernel_elf = elf_from_multiboot(mboot_ptr);

  k_init_gdt();
  k_init_idt();

  k_init_monitor();

  k_init_isr();
  k_init_irq();


  k_monitor_puts_s("inicio da ram\n");
  k_monitor_puts_hex(mboot_ptr->mmap_addr);
  k_monitor_puts_s("\n");
  k_monitor_puts_dec(mboot_ptr->mmap_addr);
  k_monitor_puts_s("\n");

  k_monitor_puts_s("fim da ram\n");
  k_monitor_puts_hex(mboot_ptr->mmap_addr + mboot_ptr->mmap_length);
  k_monitor_puts_s("\n");
  k_monitor_puts_dec(mboot_ptr->mmap_addr + mboot_ptr->mmap_length);
  k_monitor_puts_s("\n");

  k_monitor_puts_s("tamanho\n");
  k_monitor_puts_dec(mboot_ptr->mmap_length);
  k_monitor_puts_s("\n");
  k_monitor_puts_hex(mboot_ptr->mmap_length);
  k_monitor_puts_s("\n");

  k_init_pmm(mboot_ptr->mem_upper);
  // k_init_vmm();

  uint32_t i = mboot_ptr->mmap_addr;
  while (i < mboot_ptr->mmap_addr + mboot_ptr->mmap_length)
  {
    multiboot_memory_map_t *me = (multiboot_memory_map_t*) i;

    if (me->type == 1)
    {
      uint32_t j;
      for (j = me->addr_low; j < me->addr_low + me->len_low; j += K_4KB)
      {
        k_pmm_free_page(j);
      }
    }

    // the size member does not include "size" itself in its calculations so we must add sizeof(uint32_t).
    i += me->size + sizeof(uint32_t);
  }

  k_monitor_puts_s("PIT\n");
  k_init_timer();

  k_monitor_puts_s("KBD\n");
  k_init_keyboard();

  __asm__ __volatile__("sti");

  for (;;) {};

  return 0xdeadbeef;
}
