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
#include "std/system.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/irq.h"
#include "cpu/pit.h"

extern uint32_t kernel_start;
extern uint32_t kernel_end;

static device_t *vga_driver;
static device_t *serial_driver;

static gdt_entries_t gdt_entries;

static void print_mboot(const multiboot_info_t *mboot_ptr)
{
  kdebugf("MULTIBOOT raw data:\n");
  kdebugf("Flags : 0x%x\n", mboot_ptr->flags);
  kdebugf("Mem Lo: 0x%x\n", mboot_ptr->mem_lower);
  kdebugf("Mem Hi: 0x%x\n", mboot_ptr->mem_upper);
  kdebugf("Boot d: 0x%x\n", mboot_ptr->boot_device);
  kdebugf("cmdlin: 0x%x\n", mboot_ptr->cmdline);
  kdebugf("MMap  : 0x%x\n", mboot_ptr->mmap_length);
  kdebugf("Addr  : 0x%x\n", mboot_ptr->mmap_addr);
  kdebugf("Drives: 0x%x\n", mboot_ptr->drives_length);
  kdebugf("Addr  : 0x%x\n", mboot_ptr->drives_addr);
  kdebugf("Config: 0x%x\n", mboot_ptr->config_table);
  kdebugf("Loader: 0x%x\n", mboot_ptr->boot_loader_name);
  kdebugf("APM   : 0x%x\n", mboot_ptr->apm_table);
  kdebugf("VBE Co: 0x%x\n", mboot_ptr->vbe_control_info);
  kdebugf("VBE Mo: 0x%x\n", mboot_ptr->vbe_mode_info);
  kdebugf("VBE In: 0x%x\n", mboot_ptr->vbe_mode);
  kdebugf("VBE se: 0x%x\n", mboot_ptr->vbe_interface_seg);
  kdebugf("VBE of: 0x%x\n", mboot_ptr->vbe_interface_off);
  kdebugf("VBE le: 0x%x\n", mboot_ptr->vbe_interface_len);
  kdebugf("(End multiboot raw data)\n");
  kdebugf("Started with: %s\n",mboot_ptr->cmdline);
  kdebugf("Booted from: %s\n", mboot_ptr->boot_loader_name);
  kdebugf("%dkB lower memory (%dMB)\n", mboot_ptr->mem_lower, mboot_ptr->mem_lower / 1024);
  kdebugf("%dkB higher memory (%dMB)\n", mboot_ptr->mem_upper, mboot_ptr->mem_upper / 1024);
  kdebugf("Modules:\n");
  kdebugf("count: %d\n", mboot_ptr->mods_count);
  kdebugf("addr: 0x%x\n", mboot_ptr->mods_addr);
}

int kernel_main(multiboot_info_t *mboot_ptr)
{
  disable_interrupts();

  vga_driver = vga_init();
  serial_driver = serial_init();
  logging_init(vga_driver, serial_driver);

  kprintf("GDT\n");
  gdt_entries = gdt_init();

  kprintf("IDT\n");
  idt_init();

  kprintf("ISR\n");
  isr_init(gdt_entries.kcode);

  kprintf("IRQ\n");
  irq_init(gdt_entries.kcode);

  kprintf("PIT\n");
  timer_init();

  kprintf("KBD\n");
  keyboard_init();

  print_mboot(mboot_ptr);

  enable_interrupts();

  multiboot_module_t *mod = (multiboot_module_t *) mboot_ptr->mods_addr;
  callable_t cafe_babe = (callable_t)mod->mod_start;
  cafe_babe();

  return 0xdeadbeef;
}
