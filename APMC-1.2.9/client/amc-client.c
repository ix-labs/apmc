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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include "proto.h"

#define BASE_DIR "/tmp"

static char *servername;
static int son;
static struct hostent *server_host;
static unsigned int current_code_id = 0;
static int current_path_len = 0;
static int rw[2] = {-1, -1};

static char filename[1024];
static pid_t wrapper_pid;

#define debug(toto...) printf(toto)


int load_code(int code_id)
{
  int in, out;
  int r;
  char buf[4096];
  struct sockaddr_in remote;

  unlink(filename);
  current_code_id = 0;

  in = socket(AF_INET, SOCK_STREAM, 0);
  remote.sin_family = AF_INET;
  remote.sin_port = htons(CODE_PORT);
  memcpy(&remote.sin_addr, server_host->h_addr, server_host->h_length);
  debug("connecting to server\n");
  if(connect(in, (struct sockaddr*)&remote, sizeof(remote)) < 0)
    {
      perror("connect");
      close(in);
      return -1;
    }
  else
    {
      debug("creating %s\n",filename);
      out = creat( filename, 0700 );
      if(out < 0)
	{
	  close(in);
	  perror("creat");
	  return -1;
	}
      debug("sending code id : %d\n",code_id);
      if(send(in, &code_id, sizeof(int), 0) != sizeof(int))
	{
	  perror("send");
	  close(out);
	  close(in);
	  return -1;
	}
      else
	{
	  
	  do {
	    r = recv(in, buf, 4096, 0);
	    if(r > 0)
	      {
		write(out, buf, r);
		debug("writing %d in %s\n",r,filename);
	      }
	    
	  } while(r > 0);
	  if(r < 0)
	    {
	      perror("recv");
	      close(in);
	      close(out);
	      return -1;
	    }
	}
      debug("code downloaded\n");
    }
  close(in);
  close(out);
  return 0;
}
 
void do_job(struct job_request ja)
{
  if(ja.code_id == 0)
    {
      if(son)
	kill(son, SIGTERM);
      return;
    }

  if(son)
    {
      if(ja.code_id != current_code_id)
	{
	  kill(son, SIGTERM);
	  return;
	}
      else
	return;
    }

  if(ja.code_id != current_code_id)
    {
      if( load_code(ja.code_id) < 0)
	return;
      current_code_id = ja.code_id;
    }

  current_code_id  = ja.code_id;
  current_path_len = ja.path_len;

  if(rw[0]>-1)
    close(rw[0]);
  if(rw[1]>-1)
    close(rw[1]);

  if(socketpair(AF_UNIX, SOCK_STREAM, 0, rw)<0)
    {
      perror("socketpair");
      return;
    }

  son = fork();
  if( son == 0 )
    {
      char *argv[3];
      char msg[1024];
           
      argv[0] = strdup(filename);
      argv[1] = (char *)malloc(12); sprintf(argv[1], "%d", ja.path_len);
      argv[2] = NULL;
      
      close(rw[0]);
      assert( dup2(rw[1], 0) == 0 );
      assert( dup2(rw[1], 1) == 1 );
      assert( dup2(rw[1], 2) == 2 );
      
      execvp( strdup(filename), argv);
      exit(0);
    } else if (son == -1) {
      close(rw[0]);
      close(rw[1]);
      rw[0] = rw[1] = -1;
      perror("fork");
      return;
    } else {
      close(rw[1]);
      return;
    }  
}

void onchild(int s)
{
  if(getpid() == wrapper_pid)
    {
      wait(NULL);
      son = 0;
      signal(SIGCHLD, onchild);
    }
}

void onquit(int s)
{
  if(getpid() == wrapper_pid)
    {
      if(son)
	kill(son, SIGTERM);
      unlink(filename);
      current_code_id = 0;
    }
  exit(0);
}

#define max(a,b) (((a)<(b))?(b):(a))
#define MAXITERATIONWITHOUTALIVE 1024

int main(int argc, char *argv[])
{
  int fd;
  struct sockaddr_in remote;
  struct job_reply empty = { 0, 0, 0, 0};
  struct job_reply reply;
  struct job_request jr;
  int rlen;
  int r;
  fd_set rfs;
  char c;
  struct timeval tv;
  time_t t1, t2;
  int nbtest = 0;
  char hostname[1024];

  wrapper_pid = getpid();

  gethostname(hostname, 1024);
  sprintf(filename, "./amc_gc_code.%s.%d", hostname, getpid());

  if(argc != 2)
    {
      fprintf(stderr, "usage : %s <server name>\n", argv[0]);
      fprintf(stderr, " server name: mandatory argument, name of the server to connect to\n");
      exit(-33);
    }

  if( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror("socket");
      exit(-1);
    }
  remote.sin_family = AF_INET;
  remote.sin_port = htons(JOB_PORT);
  servername = strdup(argv[1]);
  if( (server_host = gethostbyname(argv[1])) == NULL)
    {
      perror("gethostbyname");
      exit(-1);
    }
  
  memcpy(&remote.sin_addr, server_host->h_addr, server_host->h_length);
  signal(SIGCHLD, onchild);
  signal(SIGINT, onquit);
  signal(SIGQUIT, onquit);
  signal(SIGHUP, onquit);
  signal(SIGTERM, onquit);

  chdir(BASE_DIR);

  while(nbtest < MAXITERATIONWITHOUTALIVE )
    {
      if(!son)
	{
	  if( sendto(fd, &empty, sizeof(empty), 0, (struct sockaddr*)&remote, sizeof(remote)) != sizeof(empty) )
	    {
	      perror("sendto");
	      exit(-1);
	    }
	  nbtest++;
	}
      FD_ZERO(&rfs);
      if(rw[0] > -1)
	{
	  FD_SET(rw[0], &rfs);
	}
      FD_SET(fd, &rfs);
      tv.tv_sec  = 3;
      tv.tv_usec = 0;
      r = select(max(fd, rw[0])+1, &rfs, NULL, NULL, &tv);
      if(r == 0)
	continue;

      if(r == -1)
	{
	  perror("select");
	  continue;
	}

      if(rw[0]>-1)
	{
	  if(FD_ISSET(rw[0], &rfs))
	    {
	      if( (read(rw[0], &reply.nbtrue, sizeof(int)) <= 0) ||
		  (read(rw[0], &reply.nbfalse, sizeof(int)) <= 0) )
		{
		  close(rw[0]);
		  rw[0] = -1;
		  continue;
		}
	      reply.code_id  = current_code_id;
	      reply.path_len = current_path_len;
	      sendto(fd, &reply, sizeof(reply), 0, (struct sockaddr*)&remote, sizeof(remote));
	    }
	}
      if(FD_ISSET(fd, &rfs))
	{
	  t1 = time(NULL);
	  rlen = sizeof(remote);
	  r = recvfrom(fd, &jr, sizeof(jr), 0, (struct sockaddr*)&remote, &rlen);
	  if( (r < 0) || (r < sizeof(struct job_request)) )
	    {
	      if(r < 0)
		perror("recvfrom");
	      continue;
	    }
	  nbtest = 0;
	  reply.nbtrue  = 0;
	  reply.nbfalse = 0;
	  do_job(jr);
	}
    }

  unlink(filename);
  current_code_id = 0;
  
  return 0;
}
