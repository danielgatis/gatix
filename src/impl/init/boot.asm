; MyOs - my os
; Copyright (C) 2014  Daniel Gatis Carrazzoni
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.


MBOOT_PAGE_ALIGN    equ 1<<0 ; load kernel and modules on a page boundary.
MBOOT_MEM_INFO      equ 1<<1 ; provide your kernel with memory info.
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; multiboot Magic value.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                     ; all instructions should be 32-bit.

[GLOBAL mboot]                ; make 'mboot' accessible from C.
[EXTERN code]                 ; start of the '.text' section.
[EXTERN bss]                  ; start of the .bss section.
[EXTERN end]                  ; end of the last loadable section.

mboot:
  dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each.
                              ; 4-byte boundary in your kernel file.
  dd  MBOOT_HEADER_FLAGS      ; how GRUB should load your file / settings.
  dd  MBOOT_CHECKSUM          ; to ensure that the above values are correct.

  dd  mboot                   ; location of this descriptor.
  dd  code                    ; start of kernel '.text' (code) section.
  dd  bss                     ; end of kernel '.data' section.
  dd  end                     ; end of kernel.
  dd  start                   ; kernel entry point (initial EIP).

[GLOBAL start]                ; kernel entry point.
[EXTERN k_main]               ; this is the entry point of our C code.

start:
  ; load multiboot information:
  push    ebx                 ; push the pointer to the Multiboot information structure.

  ; execute the kernel:
  cli                         ; disable interrupts.
  call k_main                 ; call our k_main() function.
  jmp $                       ; enter an infinite loop.
