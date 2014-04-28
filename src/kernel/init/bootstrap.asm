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

global _start

extern kernel_main
extern kernel_start
extern kernel_end

MBALIGN     equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MBALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
  dd  MAGIC
  dd  FLAGS
  dd  CHECKSUM

section .bootstrap_stack
align 4
stack_bottom:
times   16384 db 0 ; 16K
stack_top:

section .text
_start:
  mov  ax, 0x10
  mov  ds, ax
  mov  es, ax
  mov  fs, ax
  mov  gs, ax

  ; disable interruptions
  cli

  ; calculate kernel size
  mov   ecx, kernel_end
  sub   ecx, kernel_start

  ; init stack
  mov   esp, stack_top

  ; call main
  push  ebx           ; multiboot info
  push  ecx           ; kernel size
  call  kernel_main   ; main function

  ; disable interruptions
  cli

.the_end:
  hlt
  jmp   .the_end
