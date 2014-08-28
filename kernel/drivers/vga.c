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

#include "drivers/vga.h"

#include "std/system.h"
#include "std/string.h"
#include "std/utils.h"

#define CURS_CTRL       0x3d4
#define CURS_DATA       0x3d5
#define HIGH_BYTE       14
#define LOW_BYTE        15
#define COLS            80
#define ROWS            25

uint16_t *video_mem = (uint16_t *)0xB8000;

uint16_t xpos = 0;
uint16_t ypos = 0;
uint16_t attribute = 0x0700;
static device_t vga_device;

device_t *vga_init()
{
  vga_clear();

  vga_get_cursor_pos(&xpos, &ypos);

  vga_device.read = 0;
  vga_device.write = vga_write;

  return &vga_device;
}

void vga_clear()
{
  for (uint16_t i = 0; i < COLS * ROWS; ++i)
    video_mem[i] = (uint16_t)' ' | attribute;

  xpos = 0;
  ypos = 0;

  vga_set_cursor_pos(0, 0);
}

void vga_print_char(const char c)
{
  /* backspace */
  if (c == '\b')
  {
    if (xpos > 0)
    {
      --xpos;
    }
    else if (ypos > 0)
    {
      xpos = COLS - 1;
      --ypos;
    }
  }

  /* tab -> increment xpos to a point that will make it
   * divisible by 8. */
  else if (c == '\t')
  {
    xpos = (xpos + 8) & ~(8 - 1);
  }

  /* carriage return */
  else if (c == '\r')
  {
    xpos = 0;
  }

  /* newline */
  else if (c == '\n')
  {
    xpos = 0;
    ++ypos;
  }

  /* any character greater than and including a space is
   * a printable character */
  else if (c >= ' ')
  {
    uint16_t *pos = video_mem + (ypos * COLS + xpos);
    *pos = (uint16_t)c | attribute;
    ++xpos;
  }

  if (xpos >= COLS)
  {
    xpos = 0;
    ++ypos;
  }

  vga_scroll();
  vga_set_cursor_pos(xpos, ypos);
}

void vga_print_dec(const uint32_t value)
{
  int i = 0;
  char buffer[12];

  itoa(value, buffer, 10);
  while (buffer[i])
  {
    vga_print_char(buffer[i++]);
  }
}

void vga_print_hex(const uint32_t value)
{
  int i = 0;
  char buffer[12];

  itoa(value, buffer + 0, 16);
  while (buffer[i])
  {
    vga_print_char(buffer[i++]);
  }
}

void vga_print_str(const char *str)
{
  while (*str)
  {
    vga_print_char(*str++);
  }
}

void vga_set_attribute(const uint16_t attr)
{
  attribute = attr;
}

void vga_scroll()
{
  uint16_t blank, temp;

  if (ypos >= ROWS)
  {
    /* move the current text chunk back in the buffer by a line */
    temp = ypos - ROWS + 1; /* points to the start of the chunk to be moved */
    memcpy(video_mem, video_mem + temp * COLS, (ROWS - temp) * COLS * 2);

    /* finally, clear the last line */
    blank = (uint8_t)' ' | attribute;
    memsetw(video_mem + (ROWS - temp) * COLS, blank, COLS);
    ypos = ROWS - 1;
  }
}

void vga_get_cursor_pos(uint16_t *xpos, uint16_t *ypos)
{
  uint16_t pos = 0;

  outb(CURS_CTRL, HIGH_BYTE);
  pos = inb(CURS_DATA) << 8;

  outb(CURS_CTRL, LOW_BYTE);
  pos |= inb(CURS_DATA);

  *xpos = pos % COLS;
  *ypos = pos / COLS;
}

void vga_set_cursor_pos(uint16_t xpos, uint16_t ypos)
{
  uint16_t pos = ypos * COLS + xpos;

  outb(CURS_CTRL, HIGH_BYTE);
  outb(CURS_DATA, pos >> 8);

  outb(CURS_CTRL, LOW_BYTE);
  outb(CURS_DATA, pos);
}

size_t vga_write(uint8_t *data, size_t len)
{
  size_t i;

  for (i = 0; *data && i < len; ++data, ++i)
  {
    vga_print_char((const char)*data);
  }

  return i;
}
