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
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include "../config.h"
#include "struct.h"
#include "kill.h"
#include "child.h"
#include "children.h"
#include "compute.h"
#include "hosts.h"

struct s_global all;

/*
  Initialisation of global variables.
*/
static void	init_glvar(void)
{
  int	i = 0;

  all.children = malloc(all.arity * sizeof (struct s_child));
  all.workers = malloc(all.n_workers * sizeof (struct s_child));
  for (; i < all.arity; i++)
    {
      all.children[i].fd_in = -1;
      all.children[i].fd_out = -1;
      all.children[i].retry = all.children[i].connected = 0;
      all.children[i].pid = all.children[i].without_data = 0;
      all.children[i].address = NULL;
    }
  for (i = 0; i < all.n_workers; i++)
    {
      all.workers[i].fd_in = -1;
      all.workers[i].fd_out = -1;
      all.workers[i].retry = 0;
      all.workers[i].pid = 0;
      all.children[i].address = NULL;
    }
  all.no_ping = 0;
 }

int	main(int argc, char **argv)
{
  int	i = 0;

  if (argc != 6 && argc != 7)
    {
      fprintf(stderr, "%s\n", PACKAGE_STRING);
      fprintf(stderr,
	      "Usage: %s nb_path login nice_level arity n_workers [--noworker]\n",
	      argv[0]);
      fprintf(stderr, "\t--noworker : Don't launch worker on this machine\n");
      return 1;
    }
  signal(SIGPIPE, SIG_IGN);
  all.len_path = atoi(argv[1]);
  all.login_ssh = argv[2];
  all.nice_level = argv[3];
  all.arity = atoi(argv[4]);
  all.n_workers = atoi(argv[5]);
  init_glvar();
  cut_hosts();
  for (i = 0; i < all.arity; i++)
    if (all.children[i].address != NULL)
      create_child(i);
  if (argc == 6 || strcmp(argv[6], "--noworker"))
    if (compile_worker() != -1)
      {
	for (i = 0; i < all.n_workers; i++)
	  create_worker(i);
      }
  supervise_fd();
  my_zombie_killer();
  return 0;
}
