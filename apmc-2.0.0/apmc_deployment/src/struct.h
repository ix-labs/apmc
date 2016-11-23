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
#ifndef STRUCT_H_
# define STRUCT_H_

# define RETRY			3 // If connection failed, number of retry
# define CONNECTION_TIMEOUT    10 // Max number of cycles without data on child/father
# define COMPILE_TIMEOUT       30 // Max number of cycles for configure or make
# define TIMEOUT	       20 // Nodes must send data before TIMEOUT

# define SLEEP_TIME		1 // Time between each I/O request
# define COMMAND_SIZE		4 // Size of requests

// Command for launching computation on distant host
# define CHILD_CMD		{ "ssh", \
				"-o", \
				"StrictHostKeyChecking=no", \
				"-l", \
				all.login_ssh, \
				"$$HOSTNAME$$", \
				"bash -c 'di=`mktemp -d 2> /dev/null`; if [ $? -ne 0 ] ; then di=`mktemp -d /tmp/apmc.XXXXX`; \
				fi; mv /tmp/apmcdeploy-2.0.0.tar.gz /tmp/hosts_apmc /tmp/apmcworker-1.0.0.tar.gz $di; cd $di; \
				tar xfz apmcdeploy-2.0.0.tar.gz > /dev/null 2> /dev/null; cd apmcdeploy-2.0.0; \
				./configure > /dev/null; make > /dev/null; ./apmcdeploy %i %s %s %i %i; cd /tmp; rm -rf $di'; exit", \
				 NULL }

// Command for launching computation on localhost
# define WORKER_CMD		{ "nice", "-n", all.nice_level, "../apmcworker-1.0.0/apmcworker", "%i", NULL }

# define COMMAND_KILL		"KILL"
# define COMMAND_PING		"PING"

struct	s_child
{
  int	fd_in;
  int	fd_out;
  int	pid;
  int	retry;
  char  *address;
  char  without_data;
  char  connected;
};

struct s_global
{
  struct s_child *children;
  struct s_child *workers;
  int len_path;
  char no_ping;
  char *login_ssh;
  char *nice_level;
  int arity;
  int n_workers;
};
#endif
