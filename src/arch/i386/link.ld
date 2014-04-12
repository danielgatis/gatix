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

ENTRY(start)
gatix = 0x00100000;
SECTIONS {

    .text gatix : AT(gatix) {
        code = .;
        *(.text)
        *(.rodata)
        . = ALIGN(4096);
    }

    .data : AT(gatix + (data - code)) {
        data = .;
        *(.data)
        . = ALIGN(4096);
    }

    .bss : AT(gatix + (bss - code)) {
        bss = .;
        *(.bss)
        . = ALIGN(4096);
    }

    end = .;
}

