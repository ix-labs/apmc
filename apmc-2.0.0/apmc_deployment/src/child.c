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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include "struct.h"
#include "child.h"
#include "hosts.h"

extern struct s_global  all;

/*
  Creates and launches a child node using ssh connection.
  Adds its STDIN and STDOUT to our set of file descriptors.
*/
int	create_child(int n)
{

  int	fd_in[2];
  int	fd_out[2];
  int	pid;
  char *argv[] = CHILD_CMD;

  if (all.children[n].retry >= RETRY) // too many connection errors
    {
      fprintf(stderr, "Too many connection errors to %s\n", all.children[n].address);
      all.children[n].fd_in = -1;
      all.children[n].fd_out = -1;
      all.children[n].retry = all.children[n].connected = 0;
      all.children[n].pid = all.children[n].without_data = 0;
      free(all.children[n].address);
      all.children[n].address = NULL;
      if (!find_new_host(n))
	return 0;
      fprintf(stderr, "Next host : %s\n", all.children[n].address);
    }
  fprintf(stderr, "Connection to %s\n", all.children[n].address);
  pipe(fd_in);
  pipe(fd_out);
  all.children[n].fd_in = fd_in[0];
  all.children[n].fd_out = fd_out[1];
  all.children[n].without_data = all.children[n].connected = 0;
  if ((pid = fork()) == 0)
    {
      char buf[2048];
      int i;
      dup2(fd_in[1], STDOUT_FILENO);
      dup2(fd_out[0], STDIN_FILENO);
      sprintf(buf, "scp -o StrictHostKeyChecking=no -q ../apmcworker-1.0.0.tar.gz ../apmcdeploy-2.0.0.tar.gz host_%i/hosts_apmc %s@%s:/tmp > /dev/null",
	      n, all.login_ssh, all.children[n].address);
      if (system(buf))
	exit(127);
      for (i = 0; argv[i] != NULL; i++)
	{
	  if (!strcmp("$$HOSTNAME$$", argv[i]))
	    {
	      argv[i] = strdup(all.children[n].address);
	      sprintf(buf, argv[i+1], all.len_path, all.login_ssh,
		      all.nice_level, all.arity, all.n_workers);
	      argv[i+1] = buf;
	      break;
	    }
	}
      execvp(argv[0], argv);
      exit(127);
    }
  all.children[n].pid = pid;
  close(fd_in[1]);
  close(fd_out[0]);
  return 0;
}

/*
  Stops a child and relaunches it.
*/
int relaunch_child(int n)
{
  fprintf(stderr, "Connection timeout to %s\n", all.children[n].address);
  write(all.children[n].fd_out, COMMAND_KILL, COMMAND_SIZE);
  close(all.children[n].fd_in);
  close(all.children[n].fd_out);
  all.children[n].retry++;
  kill(all.children[n].pid, SIGKILL);
  return create_child(n);
}
