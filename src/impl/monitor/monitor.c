/*
 * MyOs - my os
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

#include "types.h"
#include "io.h"
#include "monitor/monitor.h"

// the VGA framebuffer starts at 0xB8000.
uint16_t *video_memory = (uint16_t *)0xB8000;

// stores the cursor position.
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

// colors
uint8_t background_color = 0;   //black
uint8_t foreground_color = 15;  //white

// chars
uint8_t SPACE = 0x20;
uint8_t TAB = 0x09;
uint8_t BACKSPACE = 0x08;

// returns a char with foreground and background color
static uint16_t k_char(uint16_t c, uint8_t foreground_color, uint8_t background_color)
{
  uint8_t attributeByte = (background_color << 4) | (foreground_color & 0x0F);
  return c | (attributeByte << 8);
}

// updates the hardware cursor.
static void k_move_cursor()
{
  // the screen is 80 characters wide.
  uint16_t cursorLocation = cursor_y * 80 + cursor_x;

  // This sends a command to indicies 14 and 15 in the
  // CRT Control Register of the VGA controller. These
  // are the high and low bytes of the index that show
  // where the hardware cursor is to be 'blinking'. To
  // learn more, you should look up some VGA specific
  // programming documents. A great start to graphics:
  // http://www.brackeen.com/home/vga.
  k_outb(0x3D4, 14);                  // tell the VGA board we are setting the high cursor byte.
  k_outb(0x3D5, cursorLocation >> 8); // send the high cursor byte.
  k_outb(0x3D4, 15);                  // tell the VGA board we are setting the low cursor byte.
  k_outb(0x3D5, cursorLocation);      // send the low cursor byte.
}

// scrolls the text on the screen up by one line.
static void k_scroll()
{
  // row 25 is the end, this means we need to scroll up
  if (cursor_y >= 25)
  {
    // move the current text chunk that makes up the screen back in the buffer by a line.
    for (int i = 0 * 80; i < 24 * 80; i++)
    {
      video_memory[i] = video_memory[i + 80];
    }

    // the last line should now be blank.
    // do this by writing 80 spaces to it.
    for (int i = 24 * 80; i < 25 * 80; i++)
    {
      video_memory[i] = k_char(SPACE, foreground_color, background_color);
    }

    // the cursor should now be on the last line.
    cursor_y = 24;
  }
}

// writes a single char.
void k_monitor_puts_c(char c)
{
  // handle a backspace, by moving the cursor back one space.
  if (c == BACKSPACE && cursor_x)
  {
    cursor_x--;
  }

  // handle a tab by increasing the cursor_x, but only to a point where it is divisible by 4.
  else if (c == TAB)
  {
    cursor_x = (cursor_x + 4) - (cursor_x % 4);
  }

  // handle carriage return.
  else if (c == '\r')
  {
    cursor_x = 0;
  }

  // handle newline by moving cursor back to left and increasing the row.
  else if (c == '\n')
  {
    cursor_x = 0;
    cursor_y++;
  }

  // handle any other printable character.
  else if (c >= SPACE)
  {
    uint16_t *location = video_memory + (cursor_y * 80 + cursor_x);
    *location = k_char(c, foreground_color, background_color);
    cursor_x++;
  }

  // check if we need to insert a new line because we have reached the end of the screen.
  if (cursor_x >= 80)
  {
    cursor_x = 0;
    cursor_y ++;
  }

  // scroll the screen if needed.
  k_scroll();

  // move the hardware cursor.
  k_move_cursor();
}

// clears the screen, by copying lots of spaces to the framebuffer.
void k_monitor_clr()
{
  for (int i = 0; i < 80 * 25; i++)
  {
    video_memory[i] = k_char(SPACE, foreground_color, background_color);
  }

  // move the hardware cursor back to the start.
  cursor_x = 0;
  cursor_y = 0;
  k_move_cursor();
}

// writes a null-terminated string.
void k_monitor_puts_s(char *c)
{
  while (*c != '\0')
  {
    k_monitor_puts_c(*c);
    c++;
  }
  k_monitor_puts_c('\n');
}
