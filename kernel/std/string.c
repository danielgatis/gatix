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

#include "std/string.h"
#include "std/types.h"

void *memcpy(void *dst, const void *src, size_t n)
{
  /*
   * memcpy does not support overlapping buffers, so always do it
   * forwards.
   * For speedy copying, optimize the common case where both pointers
   * and the length are word-aligned, and copy word-at-a-time instead
   * of byte-at-a-time. Otherwise, copy by bytes.
   */
  void *d = dst;

  if (((uint32_t)dst | (uint32_t)src | n) & 3)
  {
    __asm__ __volatile__("cld; rep movsb (%%esi), %%es:(%%edi)"
                         : "+c" (n), "+S" (src), "+D" (d)
                         : : "cc", "memory");
    return dst;
  }

  n /= 4;

  __asm__ __volatile__ ("cld; rep movsl (%%esi), %%es:(%%edi)"
                        : "+c" (n), "+S" (src), "+D" (d)
                        : : "cc", "memory");
  return dst;
}

void *memset(void *ptr, int value, size_t n)
{
  __asm__ __volatile__ ("cld; rep stosb"
                        : "+c" (n), "+D" (ptr)
                        : "a" (value)
                        : "memory");
  return ptr;
}

void *memsetw(void *ptr, unsigned short value, size_t n)
{
  __asm__ __volatile__ ("cld; rep stosw"
                        : "+c" (n), "+D" (ptr)
                        : "a" (value)
                        : "memory");
  return ptr;
}

void *memmove(void *dst, const void *src, size_t n)
{
  /* If the destination is above the source, we have to copy
   * back to front to avoid overwriting the data we want to
   * copy.
   *
   *      dst:      dddddddd
   *      src:  ssssssss   ^
   *            |   ^  |___|
   *            |___|
   *
   * If the destination is below the source, we have to copy
   * front to back.
   *
   *      dst:  dddddddd
   *      src:  ^   ssssssss
   *            |___|  ^   |
   *                   |___|
   */

  size_t i;

  if ((uintptr_t)dst < (uintptr_t)src)
  {
    /*
     * memcpy copies forwards.
     */
    return memcpy(dst, src, n);
  }

  /*
   * Copy by word in the common case.
   */
  if ((uintptr_t)dst % sizeof(long) == 0 &&
      (uintptr_t)src % sizeof(long) == 0 &&
                   n % sizeof(long) == 0)
  {

    long *d = dst;
    const long *s = src;

    /*
     * The reason we copy index i-1 and test i>0 is that
     * i is unsigned - so testing i>=0 doesn't work.
     */
    for (i = n / sizeof(long); i > 0; --i)
    {
      d[i-1] = s[i-1];
    }
  }
  else
  {
    char *d = dst;
    const char *s = src;

    for (i = n; i > 0; --i)
      d[i-1] = s[i-1];
  }

  return dst;
}

int memcmp(const void *ptr1, const void *ptr2, size_t n)
{
  const unsigned char *p1 = ptr1;
  const unsigned char *p2 = ptr2;
  size_t i;

  for (i = 0; i < n; ++i)
  {
    if (p1[i] != p2[i])
      return (int)(p1[i] - p2[i]);
  }

  return 0;
}

void *memchr(const void *ptr, int value, size_t n)
{
  const unsigned char *p = (const unsigned char *)ptr;

  while (n-- > 0)
  {
    if (*p == value)
    {
      return (void *)p;
    }

    ++p;
  };

  return NULL;
}

size_t strlen(const char *str)
{
  size_t ret = 0;
  while (str[ret++]);
  return ret;
}

size_t strnlen(const char *str, size_t n)
{
  size_t ret = 0;
  while (str[ret++] && n--);
  return ret;
}

char *strcat(char *dst, const char *src)
{
  size_t offset = strlen(dst);
  strcpy(dst + offset, src);
  return dst;
}

int strcmp(const char *s1, const char *s2)
{
  size_t i;

  for (i = 0; s1[i] != 0 && s1[i] == s2[i]; ++i);

  if (s1[i] > s2[i])
  {
    return 1;
  }
  else if (s1[i] == s2[i])
  {
    return 0;
  }

  return -1;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
  size_t i;

  for (i = 0; s1[i] != 0 && s1[i] == s2[i] && n > 0; ++i, --n);

  if (s1[i] > s2[i])
  {
    return 1;
  }
  else if (s1[i] == s2[i])
  {
    return 0;
  }

  return -1;
}

char *strcpy(char *dst, const char *src)
{
  size_t i;

  for (i = 0; src[i]; ++i)
  {
    dst[i] = src[i];
  }

  dst[i] = 0;

  return dst;
}

char *strncpy(char *dst, const char *src, size_t n)
{
  size_t i;

  for (i = 0; src[i] && n > 0; ++i, --n)
  {
    dst[i] = src[i];
  }

  for (; n > 0; ++i, --n)
  {
    dst[i] = 0;
  }

  return dst;
}
