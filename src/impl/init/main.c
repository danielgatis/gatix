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

#include "multiboot.h"
#include "monitor/monitor.h"

static void k_print_gpl()
{
  k_monitor_puts_s("Gatix");
  k_monitor_puts_s("Copyright (C) 2014  Daniel Gatis Carrazzoni");
  k_monitor_puts_s("");
  k_monitor_puts_s("This program is free software: you can redistribute it and/or modify");
  k_monitor_puts_s("it under the terms of the GNU General Public License as published by");
  k_monitor_puts_s("the Free Software Foundation, either version 3 of the License, or");
  k_monitor_puts_s("(at your option) any later version.");
  k_monitor_puts_s("");
  k_monitor_puts_s("This program is distributed in the hope that it will be useful,");
  k_monitor_puts_s("but WITHOUT ANY WARRANTY; without even the implied warranty of");
  k_monitor_puts_s("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
  k_monitor_puts_s("GNU General Public License for more details.");
  k_monitor_puts_s("");
  k_monitor_puts_s("You should have received a copy of the GNU General Public License");
  k_monitor_puts_s("along with this program.  If not, see <http://www.gnu.org/licenses/>.");
}

int k_main(multiboot_info_t *mboot_ptr)
{
  k_init_video();

  k_print_gpl();
  return 0;
}
