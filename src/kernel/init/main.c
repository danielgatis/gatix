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
#include "io/keyboard.h"

#include "std/types.h"
#include "std/utils.h"
#include "std/logging.h"

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/isr.h"
#include "arch/irq.h"
#include "arch/pit.h"

static device_t *vga_driver;
static gdt_entries_t gdt_entries;

int kernel_main(multiboot_info_t *mboot_ptr, uint32_t kernel_size)
{
  UNUSED(kernel_size);
  UNUSED(mboot_ptr);

  vga_driver = vga_init();
  logging_init(vga_driver);

  kprintf(INFO, "GDT\n");
  gdt_entries = gdt_init();

  kprintf(INFO, "IDT\n");
  idt_init();

  kprintf(INFO, "ISR\n");
  isr_init(gdt_entries.kcode);

  kprintf(INFO, "IRQ\n");
  irq_init(gdt_entries.kcode);

  kprintf(INFO, "PIT\n");
  timer_init();

  kprintf(INFO, "KBD\n");
  keyboard_init();

  __asm__ __volatile__("sti");

  for (;;) {};

  return 0xdeadbeef;
}
