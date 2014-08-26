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

#include "drivers/vga.h"
#include "drivers/serial.h"
#include "drivers/keyboard.h"

#include "std/types.h"
#include "std/utils.h"
#include "std/logging.h"

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/isr.h"
#include "arch/irq.h"
#include "arch/pit.h"

extern uint32_t kernel_start;
extern uint32_t kernel_end;

static device_t *vga_driver;
static device_t *serial_driver;

static gdt_entries_t gdt_entries;

void print_mboot(const multiboot_info_t *mboot_ptr)
{
  kprintf("MULTIBOOT raw data:\n");
  kprintf("Flags : 0x%x\n", mboot_ptr->flags);
  kprintf("Mem Lo: 0x%x\n", mboot_ptr->mem_lower);
  kprintf("Mem Hi: 0x%x\n", mboot_ptr->mem_upper);
  kprintf("Boot d: 0x%x\n", mboot_ptr->boot_device);
  kprintf("cmdlin: 0x%x\n", mboot_ptr->cmdline);
  kprintf("Mods  : 0x%x\n", mboot_ptr->mods_count);
  kprintf("Addr  : 0x%x\n", mboot_ptr->mods_addr);
  kprintf("MMap  : 0x%x\n", mboot_ptr->mmap_length);
  kprintf("Addr  : 0x%x\n", mboot_ptr->mmap_addr);
  kprintf("Drives: 0x%x\n", mboot_ptr->drives_length);
  kprintf("Addr  : 0x%x\n", mboot_ptr->drives_addr);
  kprintf("Config: 0x%x\n", mboot_ptr->config_table);
  kprintf("Loader: 0x%x\n", mboot_ptr->boot_loader_name);
  kprintf("APM   : 0x%x\n", mboot_ptr->apm_table);
  kprintf("VBE Co: 0x%x\n", mboot_ptr->vbe_control_info);
  kprintf("VBE Mo: 0x%x\n", mboot_ptr->vbe_mode_info);
  kprintf("VBE In: 0x%x\n", mboot_ptr->vbe_mode);
  kprintf("VBE se: 0x%x\n", mboot_ptr->vbe_interface_seg);
  kprintf("VBE of: 0x%x\n", mboot_ptr->vbe_interface_off);
  kprintf("VBE le: 0x%x\n", mboot_ptr->vbe_interface_len);
  kprintf("(End multiboot raw data)\n");
  kprintf("Started with: %s\n", (char *)mboot_ptr->cmdline);
  kprintf("Booted from: %s\n", (char *)mboot_ptr->boot_loader_name);
  kprintf("%dkB lower memory (%dMB)\n", mboot_ptr->mem_lower, mboot_ptr->mem_lower / 1024);
  kprintf("%dkB higher memory (%dMB)\n", mboot_ptr->mem_upper, mboot_ptr->mem_upper / 1024);
}

int kernel_main(multiboot_info_t *mboot_ptr)
{
  vga_driver = vga_init();
  serial_driver = serial_init();
  logging_init(vga_driver, serial_driver);

  kdebugf("GDT\n");
  gdt_entries = gdt_init();

  kdebugf("IDT\n");
  idt_init();

  kdebugf("ISR\n");
  isr_init(gdt_entries.kcode);

  kdebugf("IRQ\n");
  irq_init(gdt_entries.kcode);

  kdebugf("PIT\n");
  timer_init();

  kdebugf("KBD\n");
  keyboard_init();

  print_mboot(mboot_ptr);

  __asm__ __volatile__("sti");

  for (;;) {};

  return 0xdeadbeef;
}

