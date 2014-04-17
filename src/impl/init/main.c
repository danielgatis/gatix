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
#include "mm/pmm.h"

elf_t kernel_elf;

int k_main(multiboot_info_t *mboot_ptr)
{
  kernel_elf = elf_from_multiboot(mboot_ptr);

  k_init_gdt();
  k_init_idt();

  k_init_monitor();

  k_init_isr();
  k_init_irq();

  k_monitor_puts_hex(mboot_ptr->mem_upper);
  k_monitor_puts_s("\n");
  k_monitor_puts_dec(mboot_ptr->mmap_length);
  k_monitor_puts_s("\n");

  k_init_pmm(mboot_ptr->mem_upper, mboot_ptr->mmap_length);

  k_monitor_puts_s("PIT\n");
  k_init_timer();

  k_monitor_puts_s("KBD\n");
  k_init_keyboard();

  __asm__ __volatile__("sti");

  for (;;) {};

  return 0xdeadbeef;
}
