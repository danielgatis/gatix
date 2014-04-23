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

#ifndef _std_stdarg_h_
#define _std_stdarg_h_

/* width of stack = 4 bytes */
#define STACKITEM int

/* data type used for arguments */
#define va_list char *

/* Amount of space required on the stack for an arg of type TYPE.
   TYPE may alternatively be an expression whose type is used. */
#define __va_rounded_size(TYPE) \
  ((sizeof(TYPE) + sizeof(STACKITEM) - 1) & ~(sizeof(STACKITEM) - 1))

/* initialize AP so that it points to the first argument (right after LASTARG) */
#define va_start(AP, LASTARG) \
  (AP = ((va_list) &(LASTARG) + __va_rounded_size(LASTARG)))

/* do nothing */
#define va_end(AP)

/* return the next argument in the argument list and increment AP */
#define va_arg(AP, TYPE) \
  (AP += __va_rounded_size(TYPE), *((TYPE *)(AP - __va_rounded_size(TYPE))))

#endif
