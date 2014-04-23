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

#ifndef _int_irq_h_
#define _int_irq_h_

#include "std/types.h"

extern void k_irq0();
extern void k_irq1();
extern void k_irq2();
extern void k_irq3();
extern void k_irq4();
extern void k_irq5();
extern void k_irq6();
extern void k_irq7();
extern void k_irq8();
extern void k_irq9();
extern void k_irq10();
extern void k_irq11();
extern void k_irq12();
extern void k_irq13();
extern void k_irq14();
extern void k_irq15();

void k_irq_remap();

void k_irq_handler(registers_t registers);

void k_init_irq();

#endif
