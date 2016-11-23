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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "struct.h"
#include "hosts.h"

extern struct s_global  all;

static char *my_chomp(char *s)
{
  int i;
  i = strlen(s) - 1;
  while (i >= 0)
    {
      if (s[i] == ' ' || s[i] == '\n' || s[i] == '\r' || s[i] == '\t')
	s[i] = 0;
      else
	break;
      i--;
    }
  if (i < 0)
    return NULL;
  return s;
}

/*
  Cuts hosts file in arity files and assigns hostname of children.
*/
int cut_hosts(void)
{
  FILE **fp;
  FILE *fr;
  int i, j;
  char buf[1024];
  char *buf2;

  fp = malloc(all.arity * sizeof (FILE *));
  if ((fr = fopen("../hosts_apmc", "r")) == NULL)
    return 0;
  for (i = 0; i < all.arity; i++)
    {
      sprintf(buf, "host_%i", i);
      mkdir(buf, 0755);
      sprintf(buf, "host_%i/hosts_apmc", i);
      fp[i] = fopen(buf, "w");
    }
  for (i = 0; i < all.arity; i++)
    {
      do
	if (fgets(buf, 1023, fr) == NULL)
	  {
	    for (j = 0; j < all.arity; j++)
	      fclose(fp[j]);
	    return i;
	  }
      while (!strncmp(buf, "//", 2) || (buf2 = my_chomp(buf)) == NULL);
      all.children[i].address = strdup(buf2);
    }
  i = 0;
  while (fgets(buf, 1023, fr) != NULL)
    {
      if (!strncmp(buf, "//", 2))
	continue;
      fputs(buf, fp[i++ % all.arity]);
    }
  fclose(fr);
  for (i = 0; i < all.arity; i++)
    fclose(fp[i]);
  return all.arity;
}

/*
  Updates address field. When a host is unreachable, finds next host.
*/
int find_new_host(int n)
{
  char buf1[1024];
  char buf2[1024];
  char buf[1024];
  FILE *fr;
  FILE *fw;

  sprintf(buf1, "host_%i/hosts_apmc", n);
  sprintf(buf2, "host_%i/hosts_old", n);
  rename(buf1, buf2);
  fr = fopen(buf2, "r");
  if (fgets(buf, 1024, fr) == NULL)
    {
      fclose(fr);
      return 0;
    }
  if (buf[strlen(buf) - 1] == '\n')
    buf[strlen(buf) - 1] = 0;
  all.children[n].address = strdup(buf);
  fw = fopen(buf1, "w");
  while (fgets(buf, 1023, fr) != NULL)
    fputs(buf, fw);
  fclose(fr);
  fclose(fw);
  remove(buf2);
  return 1;
}
