/* APMC - Approximate Model Checker
 * Copyright (C) 2003 Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
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

#include <gtk/gtk.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gtkbfs.h"

#include "interface.h"
#include "support.h"
#include "callbacks.h"
#include "reactive-modules.h"
#include "compilers.h"

#include <unistd.h> 
#define _GNU_SOURCE
#include <getopt.h>

static char *possible_dirs[] = 
  { "./", "../", "../examples/", "examples/", "server/examples/", NULL };

int
main (int argc, char *argv[])
{
  GtkWidget *window1;
  struct timeval tv;
  char **d;
  char filename[1024];
  struct stat s;

  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);

  for(d = possible_dirs; *d; d++)
    {
      sprintf(filename, "%sphil5.pm", *d);
      if(stat(filename, &s) == 0)
	  break;
    }
  if(*d) 
    example_dir = *d;

  gtk_init (&argc, &argv);

  window1 = create_window1 ();
  gtk_widget_show (window1);

  PMFILE = (struct pmfile *)calloc(1, sizeof(struct pmfile));

  gtk_main ();

  close(g_io_channel_unix_get_fd(code_server));
  close(g_io_channel_unix_get_fd(job_server));

  return 0;
}

