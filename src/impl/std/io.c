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

#include "std/io.h"

void k_outb(uint16_t port, uint8_t value)
{
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t k_inb(uint16_t port)
{
  uint8_t ret;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

uint16_t k_inw(uint16_t port)
{
  uint16_t ret;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}
