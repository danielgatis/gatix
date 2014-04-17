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

#ifndef _output_monitor_h_
#define _output_monitor_h_

#include "std/types.h"

void k_init_monitor();

void k_set_text_color(uint8_t foreground_color, uint8_t background_color);

void k_monitor_puts_c(char c);

void k_monitor_puts_s(char *c);

void k_monitor_puts_dec(int32_t n);

void k_monitor_puts_hex(int32_t n);

void k_monitor_clr();

#endif
