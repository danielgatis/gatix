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

#ifndef _std_logging_h
#define _std_logging_h

typedef enum
{
    DEBUG = 0,      /* debug information */
    INFO,           /* unimportant */
    NOTICE,         /* important, but not bad */
    WARNING,        /* not what was expected, but still okay */
    ERROR,          /* this is bad... */
    CRITICAL        /* fatal error */
} log_level_t;

void logging_init();

int kprintf(log_level_t level, const char *fmt, ...);

#endif
