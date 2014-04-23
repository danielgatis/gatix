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

#ifndef _std_types_h
#define _std_types_h

#define K_4K 0x1000
#define K_1M 0x100000

#include <stdint.h>

typedef struct registers
{
  uint32_t ds;
  uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, esp, ss;
} registers_t;

#endif
