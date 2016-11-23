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
// #include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "struct.h"
#include "kill.h"

extern struct s_global	all;
/*
void print_usage(void)
{
  struct rusage usage;
  FILE *res;
  if ((res = fopen("/home/stud/lrde-2007/guirad_g/logs/apmc", "a")) == NULL)
    return;
  getrusage(RUSAGE_SELF, &usage);
  fprintf(res, "utime:%li,stime:%li,maxrss:%li,ixrss:%li,idrss:%li,isrss:%li\
,minflt:%li,majflt:%li,nswap:%li,inblock:%li,oublock:%li,msgsnd:%li,msgrcv:%li\
nsignals:%li,nvcsw:%li,nivcsw:%li\n",usage.ru_utime.tv_sec, usage.ru_stime.tv_sec,
	  usage.ru_maxrss, usage.ru_ixrss, usage.ru_idrss, usage.ru_isrss,
	  usage.ru_minflt, usage.ru_majflt, usage.ru_nswap, usage.ru_inblock,
	  usage.ru_oublock, usage.ru_msgsnd, usage.ru_msgrcv, usage.ru_nsignals,
	  usage.ru_nvcsw, usage.ru_nivcsw);
  getrusage(RUSAGE_CHILDREN, &usage);
  fprintf(res, "utime:%li,stime:%li,maxrss:%li,ixrss:%li,idrss:%li,isrss:%li\
,minflt:%li,majflt:%li,nswap:%li,inblock:%li,oublock:%li,msgsnd:%li,msgrcv:%li\
nsignals:%li,nvcsw:%li,nivcsw:%li\n",usage.ru_utime.tv_sec, usage.ru_stime.tv_sec,
	  usage.ru_maxrss, usage.ru_ixrss, usage.ru_idrss, usage.ru_isrss,
	  usage.ru_minflt, usage.ru_majflt, usage.ru_nswap, usage.ru_inblock,
	  usage.ru_oublock, usage.ru_msgsnd, usage.ru_msgrcv, usage.ru_nsignals,
	  usage.ru_nvcsw, usage.ru_nivcsw);
  fclose(res);
}
*/
/*
  Kills all zombies if exists.
*/
int		my_zombie_killer(void)
{
  int		pid;
  int		status;
  int		n_zombie = 0;

  while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    n_zombie++;
  return n_zombie;
}

/*
  Kills children, kills workers and exits.
*/
void	kill_and_exit(const char * why)
{
  int	i = 0;
  char buf[512];
  char buf2[550];

  gethostname(buf, 512);
  fprintf(stderr, "Killing (%i) -%s- (reason : %s)\n",
	  getpid(), buf, why);
  for (i = 0; i < all.arity; i++)
    if (all.children[i].fd_out != -1)
      {
	write(all.children[i].fd_out, COMMAND_KILL, COMMAND_SIZE);
	close(all.children[i].fd_out);
      }
  for (i = 0; i < all.n_workers; i++)
    if (all.workers[i].pid)
      kill(all.workers[i].pid, SIGKILL);
  my_zombie_killer();
  getcwd(buf, 512);
  buf[strrchr(buf, '/') - buf] = '\0';
  sprintf(buf2, "rm -rf %s", buf);
  system(buf2);
  for (i = 0; i < all.arity; i++)
    kill(all.children[i].pid, SIGKILL);
  my_zombie_killer();
  // print_usage();
  exit(0);
}
