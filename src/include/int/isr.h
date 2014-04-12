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

#ifndef _int_isr_h_
#define _int_isr_h_

#include "std/types.h"

extern void k_isr0();
extern void k_isr1();
extern void k_isr2();
extern void k_isr3();
extern void k_isr4();
extern void k_isr5();
extern void k_isr6();
extern void k_isr7();
extern void k_isr8();
extern void k_isr9();
extern void k_isr10();
extern void k_isr11();
extern void k_isr12();
extern void k_isr13();
extern void k_isr14();
extern void k_isr15();
extern void k_isr16();
extern void k_isr17();
extern void k_isr18();
extern void k_isr19();
extern void k_isr20();
extern void k_isr21();
extern void k_isr22();
extern void k_isr23();
extern void k_isr24();
extern void k_isr25();
extern void k_isr26();
extern void k_isr27();
extern void k_isr28();
extern void k_isr29();
extern void k_isr30();
extern void k_isr31();

void k_init_isr();

void k_isr_handler(registers_t *registers);

#endif
