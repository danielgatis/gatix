; Gatix
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

bits 32

MBALIGN     equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MBALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

extern kernel_start
extern kernel_end

section .multiboot
align 4
  dd MAGIC
  dd FLAGS
  dd CHECKSUM

section .bootstrap_stack
align 4
  stack_bottom:
  times 16384 db 0
  stack_top:

section .text
global start
start:
  ; init stack
  mov   esp, stack_top

  ; multiboot info
  push  ebx

  ; call main
  extern kernel_main
  call  kernel_main

  ; disable interrupts
  cli

.hang:
  hlt
  jmp  .hang
