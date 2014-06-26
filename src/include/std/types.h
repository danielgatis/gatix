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

#include <stdint.h>

#define NULL ((void *)0ul)
#define TRUE  1
#define FALSE 0

typedef int bool;
typedef unsigned int uintptr_t;
typedef unsigned int addr_t;
typedef unsigned int size_t;

typedef struct
{
  size_t (*read) (uint8_t *data, size_t len);
  size_t (*write)(uint8_t *data, size_t len);
} device_t;

typedef device_t *(driver_init)(void);

typedef struct
{
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

#endif
