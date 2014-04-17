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

// #ifndef _mm_heap_h_
// #define _mm_heap_h_

// #define K_HEAP_START 0xD0000000
// #define K_HEAP_END   0xFFBFF000

// #include "std/types.h"

// typedef struct header
// {
//   struct header *prev, *next;
//   uint32_t allocated : 1;
//   uint32_t length : 31;
// } header_t;

// void k_init_heap();

// // Returns a pointer to a chunk of memory, minimum size 'l' bytes.
// void *k_malloc (uint32_t l);

// // Returns a pointer to a chunk of memory, minimum size 'l' bytes,
// // and zero it's contents
// void *k_cmalloc (uint32_t l);

// // Takes a chunk of memory allocated with kmalloc, and returns it to the pool of usable memory.
// void k_free (void *p);

// #endif
