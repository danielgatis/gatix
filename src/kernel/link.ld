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

OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
phys = 0x00100000;
SECTIONS
{
  .text phys : AT(phys) {
    code = .;
    *(.multiboot*)
    *(.text*)
    *(.rodata*)
    . = ALIGN(4096);
  }


  .data : AT(phys + (data - code))
  {
    data = .;
    *(.data*)
    . = ALIGN(4096);
  }

  .bss : AT(phys + (bss - code))
  {
    bss = .;
    *(.bss*)
    . = ALIGN(4096);
  }

  end = .;

  /DISCARD/ : {
    *(.comment)
    *(.eh_frame)
    *(.note.gnu.build-id)
    *(.debug_abbrev)
    *(.debug_info)
    *(.debug_line)
    *(.debug_loc)
    *(.debug_pubnames)
    *(.debug_aranges)
    *(.debug_str)
    *(.debug_macinfo)
    *(.debug_ranges)
    *(.stab)
    *(.stabstr)
  }
}
