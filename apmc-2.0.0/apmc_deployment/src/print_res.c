/* APMC - Approximate Model Checker
 * Copyright (C) 2005 Guillaume Guirado, Thomas Herault, Frederic Magniett and Sylvain Peyronnet
 *
 * This software is free software; you can redistributed it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful, but
 * WIHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this software; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "print_res.h"

/*
  Prints data using special format :
  OK:NB  where nb = 17 char
*/
static void format_data(char *type, long int *nb)
{
  static char buf[25];
  static char buf_res[25];
  int  n;

  sprintf(buf, "%lx", *nb);
  sprintf(buf_res, "%s:0x", type);
  n = 20 - strlen(buf_res) - strlen(buf);
  while (n-- > 0)
    strcat(buf_res, "0");
  printf("%s%s", buf_res, buf);
}

/*
  Prints collected results on stdout.
*/
void send_data(long int *path_ok, long int *path_ko)
{
  if (*path_ok)
    format_data("OK", path_ok);
  if (*path_ko)
    format_data("KO", path_ko);
  if (*path_ok == 0 && *path_ko == 0)
    format_data("KO", path_ko);
  *path_ok = *path_ko = 0;
}
