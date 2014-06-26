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

#include "drivers/serial.h"

#include "arch/arch.h"

#include "std/vsprintf.h"

#define SERIAL_DATA(base)               (base)
#define SERIAL_DLL(base)                (base + 0) /* divisor latch low byte */
#define SERIAL_DLH(base)                (base + 1) /* divisor latch high byte */
#define SERIAL_INT_ENABLE(base)         (base + 1) /* interrupt enable register */
#define SERIAL_INT_IDENT(base)          (base + 2) /* interrupt identification register */
#define SERIAL_FIFO_CTRL(base)          (base + 2) /* FIFO control register */
#define SERIAL_LINE_CTRL(base)          (base + 3) /* line control register */
#define SERIAL_MODEM_CTRL(base)         (base + 4) /* modem control register */
#define SERIAL_LINE_STATUS(base)        (base + 5) /* line status register */
#define SERIAL_MODEM_STATUS(base)       (base + 6) /* modem status register */
#define SERIAL_SCRATCH(base)            (base + 7) /* scratch register */

static uint16_t com;
static device_t com_device;

static int is_transmit_empty(void);
static void write_char(char c);

device_t *serial_init(void)
{
  const char *init_message = "\nSerial output\n";

  uint16_t divisor = 3; /* 115200 / 3 = 38400 Hz */

  /* get the base address of COM1 port in the BDA */
  com = *((uint16_t *)(0x0400));

  outb(SERIAL_INT_ENABLE(com), 0x00);     /* disable interrupts */
  outb(SERIAL_LINE_CTRL(com), 0x80);      /* enable DLAB */
  outb(SERIAL_DLL(com), divisor);         /* send divisor low byte */
  outb(SERIAL_DLH(com), divisor >> 8);    /* send divisor high byte */

  /* Bit:     | 7    | 6     | 5 4 3  | 2    | 1 0     |
   * Content: | DLAB | break | parity | stop | length  |
   * Value:   | 0    | 0     | 0 0 0  | 0    | 1 1     | = 0x03
   * Means: length of 8 bits, no parity bit, one stop bit and break control disabled.
   */
  outb(SERIAL_LINE_CTRL(com), 0x03);

  /* Bit:     | 7 6         | 5        | 4   | 3        | 2              | 1               | 0            |
   * Content: | trig. level | 64B FIFO | res | DMA mode | clear tr. FIFO | clear rec. FIFO | enable FIFOs |
   * Value:   | 1 1         | 0        | 0   | 0        | 1              | 1               | 1            | = 0xc7
   * Means: 14 bytes stored trigger interrupt, 16 bytes buffer, clear both receiver and
   *        transmission FIFO queues, enable FIFOs.
   * http://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming#FIFO_Control_Register
   */
  outb(SERIAL_FIFO_CTRL(com), 0xc7);

  /* Bit:     | 7 6 | 5        | 4        | 3           | 2           | 1   | 0   |
   * Content: | res | autoflow | loopback | aux. out. 2 | aux. out. 1 | rts | dtr |
   * Value:   | 0 0 | 0        | 0        | 1           | 0           | 1   | 1   | = 0x0b
   * Means: request to send (RTS) and data terminal ready (DTR) meaning we are ready to
   *        send data, enable interrupts (auxiliary output 2 = 1).
   */
  outb(SERIAL_MODEM_CTRL(com), 0x0b);

  //outb(SERIAL_INT_ENABLE(com), 0x01); /* enable interrupts on receive */

  com_device.read = 0;
  com_device.write = write;

  while (*init_message)
  {
    write_char(*init_message++);
  }

  return &com_device;
}

size_t write(uint8_t *data, size_t len)
{
  size_t i;

  for (i = 0; *data && i < len; ++data, ++i) 
  {
    write_char(*data);
  }

  return i;
}

static int is_transmit_empty(void)
{
  return inb(SERIAL_LINE_STATUS(com)) & 0x20;
}

static void write_char(char c)
{
  while (is_transmit_empty() == 0) ;
  outb(SERIAL_DATA(com), c);
}
