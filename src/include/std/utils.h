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

#ifndef _std_utils_h
#define _std_utils_h

#include "types.h"

#define is_upper(c)  ((c) >= 'A' && (c) <= 'Z')
#define to_lower(c)  (is_upper(c) ? (((c) - 'A') + 'a') : (c))
#define is_alpha(c)  (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
#define is_digit(c)  ((c) >= '0' && (c) <= '9')
#define is_alnum(c)  (is_alpha(c) || is_digit(c))
#define is_xdigit(c) (is_digit(c) || ((c) > 'a' && (c) < 'f'))
#define UNUSED(x) (void)(x)

long int strtol(const char *str, char **endptr, int base);
char *itoa(unsigned long value, char *str, int base);
int   atoi(char *str);

#endif
