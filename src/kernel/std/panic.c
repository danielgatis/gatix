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

#include "std/panic.h"
#include "std/elf.h"
#include "io/monitor.h"

extern elf_t kernel_elf;

void k_panic(char *msg)
{
  k_monitor_puts_s("System panic: ");
  k_monitor_puts_s(msg);
  k_monitor_puts_c('\n');

  k_print_stack_trace();

  __asm__ __volatile__ ("cli");
  __asm__ __volatile__ ("hlt");
}

void k_print_stack_trace()
{
  uint32_t *ebp, *eip;
  __asm__ __volatile__ ("mov %%ebp, %0" : "=r" (ebp));
  while (ebp)
  {
    eip = ebp + 1;
    k_monitor_puts_s("\t[");
    k_monitor_puts_hex(*eip);
    k_monitor_puts_s("]\t");
    k_monitor_puts_s(elf_lookup_symbol(*eip, &kernel_elf));
    ebp = (uint32_t*) *ebp;
  }
}
