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

#include "arch/pit.h"
#include "arch/idt.h"
#include "arch/arch.h"

#include "std/utils.h"

uint32_t timer_ticks = 0;

void timer_phase(uint32_t frequency)
{
  uint32_t divisor = 1193180 / frequency;
  outb(0x43, 0x36);

  uint8_t l = (uint8_t)(divisor & 0xFF);
  uint8_t h = (uint8_t)((divisor>>8) & 0xFF);

  outb(0x40, l);
  outb(0x40, h);
}

void timer_handler(registers_t *registers)
{
  UNUSED(registers);

  timer_ticks++;
}

void timer_init()
{
  timer_phase(50);
  idt_set_handler(0, timer_handler);
}
