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

#include "init/multiboot.h"

#include "io/vga.h"
#include "io/serial.h"
#include "io/keyboard.h"

#include "std/types.h"
#include "std/utils.h"
#include "std/logging.h"

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/isr.h"
#include "arch/irq.h"
#include "arch/pit.h"

#include "mm/pmm.h"

static device_t *vga_driver;
static device_t *serial_driver;

static gdt_entries_t gdt_entries;

int kernel_main(multiboot_info_t *mboot_ptr, uint32_t kernel_size)
{
  vga_driver = vga_init();
  serial_driver = serial_init();
  logging_init(vga_driver, serial_driver);

  kprintf(DEBUG, "GDT\n");
  gdt_entries = gdt_init();

  kprintf(DEBUG, "IDT\n");
  idt_init();

  kprintf(DEBUG, "ISR\n");
  isr_init(gdt_entries.kcode);

  kprintf(DEBUG, "IRQ\n");
  irq_init(gdt_entries.kcode);

  kprintf(DEBUG, "PMM\n");
  pmm_init(mboot_ptr, (mboot_ptr->mem_upper + mboot_ptr->mem_lower) * 1024, kernel_size);

  kprintf(DEBUG, "PIT\n");
  timer_init();

  kprintf(DEBUG, "KBD\n");
  keyboard_init();

  __asm__ __volatile__("sti");

  for (;;) {};

  return 0xdeadbeef;
}
