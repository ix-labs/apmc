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
#include <sys/time.h>
#include <sys/types.h>
#include "../config.h"
#ifdef HAVE_SYS_FILIO_H
# include <sys/filio.h>
#endif

#include "struct.h"
#include "kill.h"
#include "child.h"
#include "children.h"
#include "compute.h"
#include "print_res.h"

extern struct s_global	all;

/*
  Reads data from a child.
*/
static void	read_child(int n, long int *path_ok, long int *path_ko)
{
  int		n_read;
  char		buf[25];
  long int	n_ok = -1;
  long int	n_ko = -1;

  ioctl(all.children[n].fd_in, FIONREAD, &n_read);
  if (n_read == 0) // Child is dead :(
    {
      kill(all.children[n].pid, SIGKILL);
      all.children[n].retry++;
      close(all.children[n].fd_in);
      close(all.children[n].fd_out);
      fprintf(stderr, "Dead child\n");
      create_child(n);
      return;
    }
  if (n_read < 20) // not enough data to read
    all.children[n].without_data++;
  while (n_read >= 20)
    {
      all.children[n].retry = all.children[n].without_data = 0;
      memset(buf, 0, 25);
      read(all.children[n].fd_in, buf, 20);
      if (sscanf(buf, "KO:%li", &n_ko))
	{
	  all.children[n].connected = 1;
	  *path_ko += n_ko;
	}
      if (sscanf(buf, "OK:%li", &n_ok))
	{
	  all.children[n].connected = 1;
	  *path_ok += n_ok;
	}
      if (n_ok < 0 && n_ko < 0)
	fprintf(stderr, "Corrupted data\n"); // FIXME : bad formated data
      n_read -= 20;
    }
}

/*
  Sends a message to children
*/
static void send_to_all(char *s)
{
  int i;

  for (i = 0; i < all.arity; i++)
    {
      if (all.children[i].fd_out != -1)
	write(all.children[i].fd_out, s, strlen(s));
    }
}

/*
  Reads command from stdin.
  FIXME
*/
static void	read_stdin(void)
{
  int	n_read;
  char	buf[COMMAND_SIZE + 1];

  ioctl(STDIN_FILENO, FIONREAD, &n_read);
   if (n_read == 0)
     kill_and_exit("stdin closed");
   if (n_read >= COMMAND_SIZE)
    {
      all.no_ping = 0;
      memset(buf, 0, COMMAND_SIZE + 1);
      read(STDIN_FILENO, buf, COMMAND_SIZE);
      if (!strcmp(buf, COMMAND_KILL))
	kill_and_exit("kill command received from father");
      if (!strcmp(buf, COMMAND_PING))
	{
	  send_to_all(buf);
	  return;
	}
      // Unknown command, it's an error !
      fprintf(stderr, "Unknown command : %s\n", buf);
      //      kill_and_exit();
    }
}

static void add_all_fd(fd_set *all_fd)
{
  int i;

  FD_ZERO(all_fd);
  for (i = 0; i < all.arity; i++) // Tests all possible children
    if (all.children[i].fd_in != -1) // Only connected children
      {
	if (all.children[i].connected == 0)
	  {
	    if (all.children[i].without_data > COMPILE_TIMEOUT)
	      relaunch_child(i);
	    else
	      FD_SET(all.children[i].fd_in, all_fd);
	  }
	else
	  {
	    if (all.children[i].without_data > CONNECTION_TIMEOUT)
	      relaunch_child(i);
	    else
	      FD_SET(all.children[i].fd_in, all_fd);
	  }
      }
  for (i = 0; i < all.n_workers; i++)
    if (all.workers[i].fd_in != -1)
      {
	FD_SET(all.workers[i].fd_in, all_fd);
	write(all.workers[i].fd_out, "i", 1);
      }
  FD_SET(STDIN_FILENO, all_fd);
}

/*
  Waits for data to read from children or workers.
*/
void supervise_fd(void)
{
  long int	path_ok = 0;
  long int	path_ko = 0;
  struct timeval timeout;
  int		i = 0;
  fd_set	all_fd;

  for (; ; )
    {
      add_all_fd(&all_fd);
      timeout.tv_sec = TIMEOUT;
      timeout.tv_usec = 0;
      switch(select(FD_SETSIZE, &all_fd, NULL, NULL, &timeout))
	{
	  case 0: // Timeout all
	    kill_and_exit("Received no ata from nowhere...Argh!");
	    break;
	  case -1: // Error on select
	    kill_and_exit("Select error");
	    break;
	  default:
	    if (FD_ISSET(STDIN_FILENO, &all_fd))
	      read_stdin();
	    else
	      if (all.no_ping++ >= CONNECTION_TIMEOUT)
		kill_and_exit("no ping from father received");
	    for (i = 0; i < all.arity; i++)
	      if (all.children[i].fd_in != -1)
		{
		  if (FD_ISSET(all.children[i].fd_in, &all_fd))
		    read_child(i, &path_ok, &path_ko);
		  else
		    all.children[i].without_data++;
		}
	    for (i = 0; i < all.n_workers; i++)
	      if (all.workers[i].fd_in != -1 &&
		  FD_ISSET(all.workers[i].fd_in, &all_fd))
		read_worker(i, &path_ok, &path_ko);
	    break;
	}
      send_data(&path_ok, &path_ko);
      if(fflush(stdout))
	kill_and_exit("can't write on stdout");
      sleep(SLEEP_TIME);
      my_zombie_killer();
    }
}

