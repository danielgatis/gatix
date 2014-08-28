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

#ifndef _std_string_h_
#define _std_string_h_

#include "std/types.h"

void *memcpy(void *dst, const void *src, size_t n);
void *memset(void *ptr, int value, size_t n);
void *memsetw(void *ptr, unsigned short value, size_t n);
void *memmove(void *dst, const void *src, size_t n);
int memcmp(const void *ptr1, const void *ptr2, size_t n);
void *memchr(const void *ptr, int value, size_t n);

size_t strlen(const char *str);
size_t strnlen(const char *str, size_t maxlen);

char *strcat(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);

#endif
