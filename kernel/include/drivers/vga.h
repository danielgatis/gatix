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

#ifndef _drivers_vga_h_
#define _drivers_vga_h_

#include "std/types.h"

device_t *vga_init();

void vga_clear();
void vga_scroll();

void vga_print_char(const char c);
void vga_print_dec(const uint32_t value);
void vga_print_hex(const uint32_t value);
void vga_print_str(const char *str);

void vga_get_cursor_pos(uint16_t *xpos, uint16_t *ypos);
void vga_set_cursor_pos(uint16_t xpos, uint16_t ypos);
void vga_set_attribute(const uint16_t attr);

size_t vga_write(uint8_t *data, size_t len);

#endif
