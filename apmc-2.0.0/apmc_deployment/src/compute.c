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
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include "../config.h"
#ifdef HAVE_SYS_FILIO_H
# include <sys/filio.h>
#endif

#include "struct.h"
#include "compute.h"

extern struct s_global	all;

int compile_worker(void)
{
  if (system("(cd ..; tar xfz apmcworker-1.0.0.tar.gz > /dev/null 2> /dev/null; cd \
apmcworker-1.0.0; ./configure > /dev/null; make > /dev/null 2> /dev/null)"))
    {
      char buf[512];
      gethostname(buf, 512);
      fprintf(stderr, "Unable to compile worker properly on %s\n", buf);
      return -1;
    }
  return 0;
}

/*
  Launch computation on localhost
*/
int create_worker(int n)
{
  int	fd_in[2];
  int	fd_out[2];
  int	pid;
  char	*argv[] = WORKER_CMD;
  char *buf;

  pipe(fd_in);
  pipe(fd_out);
  all.workers[n].fd_in = fd_in[0];
  all.workers[n].fd_out = fd_out[1];
  if ((pid = fork()) == 0)
    {
      dup2(fd_in[1], STDOUT_FILENO);
      dup2(fd_out[0], STDIN_FILENO);
      buf = malloc(strlen(argv[4]) + 20);
      sprintf(buf, argv[4], all.len_path);
      argv[4] = buf;
      execvp(argv[0], argv);
      exit(127);
    }
  all.workers[n].pid = pid;
  close(fd_in[1]);
  close(fd_out[0]);
  return 0;
}

/*
  Reads data from a worker.
*/
void	read_worker(int n, long int *path_ok, long int *path_ko)
{
  int		n_read;
  char		buf[25];
  long int	n_ok = -1;
  long int	n_ko = -1;

  ioctl(all.workers[n].fd_in, FIONREAD, &n_read);
  if (n_read == 0) // Worker is dead :(
    {
      close(all.workers[n].fd_in);
      close(all.workers[n].fd_out);
      fprintf(stderr, "Dead worker\n");
      create_worker(n);
      return;
    }
  if (n_read < 20 && all.workers[n].retry++) // not enough data to read (is it possible ?)
    if (all.workers[n].retry > RETRY)
      {
	kill(all.workers[n].pid, SIGKILL);
	create_worker(n);
      }
  while (n_read >= 20)
    {
      all.workers[n].retry = 0;
      memset(buf, 0, 25);
      read(all.workers[n].fd_in, buf, 20);
      if (sscanf(buf, "KO:%li", &n_ko))
	*path_ko += n_ko;
      if (sscanf(buf, "OK:%li", &n_ok))
	*path_ok += n_ok;
      if (n_ok < 0 && n_ko < 0)
	return; // FIXME : bad formated data (impossible !)
      n_read -= 20;
    }
}
