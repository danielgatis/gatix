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

#include "std/elf.h"
#include "std/string.h"

elf_t elf_from_multiboot(multiboot_info_t *mb)
{
  elf_t elf;

  multiboot_elf_section_header_table_t *elf_sec = &(mb->u.elf_sec);
  elf_section_header_t *sh = (elf_section_header_t*)elf_sec->addr;
  uint32_t shstrtab = sh[elf_sec->shndx].addr;

  for (uint32_t i = 0; i < elf_sec->num; i++)
  {
    char *name = (char *) (shstrtab + sh[i].name);

    if (!strcmp (name, ".strtab"))
    {
      elf.strtab = (char *)sh[i].addr;
      elf.strtabsz = sh[i].size;
    }

    if (!strcmp (name, ".symtab"))
    {
      elf.symtab = (elf_symbol_t*)sh[i].addr;
      elf.symtabsz = sh[i].size;
    }
  }

  return elf;
}

char *elf_lookup_symbol(uint32_t addr, elf_t *elf)
{
  for (uint32_t i = 0; i < (elf->symtabsz/sizeof (elf_symbol_t)); i++)
  {
    char *name = (char *) ((uint32_t)elf->strtab + elf->symtab[i].name);

    if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2)
      continue;

    if ( (addr >= elf->symtab[i].value) &&
      (addr < (elf->symtab[i].value + elf->symtab[i].size)) )
    {
      return name;
    }
  }
  return "";
}
