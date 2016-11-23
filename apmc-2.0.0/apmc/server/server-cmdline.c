/* APMC - Approximate Model Checker
 * Copyright (C) 2003, 2005 Guillaume Guirado, Thomas H	rault, Frederic Magniett and Sylvain Peyronnet
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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../config.h"
#ifdef HAVE_SYS_FILIO_H
# include <sys/filio.h>
#endif

#include "reactive-modules.h"
#include "apmc.h"
#include "compilers.h"

int ltl_parse();
void init_library_apmc(void);

#define TIMEWAIT 1
#define MAX_START_TIME 100 // Max time with 0 ok & 0 ko path ! (in seconds)

#define CODE_SOURCE  "worker/amc_gc_code.c"

# define CHILD_CMD		{ "ssh", \
				"-o", \
				"StrictHostKeyChecking=no", \
				"-l", \
				login_ssh, \
				"$$HOSTNAME$$", \
				"bash -c 'di=`mktemp -d 2> /dev/null`; if [ $? -ne 0 ] ; then di=`mktemp -d /tmp/apmc.XXXXX`; \
				fi; mv /tmp/apmcdeploy-2.0.0.tar.gz /tmp/hosts_apmc /tmp/apmcworker-1.0.0.tar.gz $di; cd $di; \
				tar xfz apmcdeploy-2.0.0.tar.gz > /dev/null ; cd apmcdeploy-2.0.0; \
				./configure > /dev/null; make > /dev/null; ./apmcdeploy %i %s %s %s %s --noworker; cd /tmp; rm -rf $di'; exit", \
				 NULL }

#define MAXFD 1024

void free_LTL();
extern FILE *ltl_in;

int ltl_lineno;
struct exprlist *LTL = NULL;

/* static int   current_code_id; // FIXME */
static int   current_path_len;
static long int   current_job_true;
static long int   current_job_false;
static int   istream;
static int   ostream;
static int   pid;
static int   worker_pid;
static char *login_ssh;
static char *nice_level;
static char *arity;
static char *n_workers;

/*
  Creates and launches a child node using ssh connection.
  Adds its STDIN and STDOUT to our set of file descriptors.
*/
int	create_child(int current_path_len)
{

  int	fd_in[2];
  int	fd_out[2];
  char *argv[] = CHILD_CMD;

  pipe(fd_in);
  pipe(fd_out);
  istream = fd_in[0];
  ostream = fd_out[1];
  if ((pid = fork()) == 0)
    {
      char buf[2048];
      int i;
      dup2(fd_in[1], STDOUT_FILENO);
      dup2(fd_out[0], STDIN_FILENO);
      sprintf(buf, "scp -o StrictHostKeyChecking=no -q worker/apmcworker-1.0.0.tar.gz apmcdeploy-2.0.0.tar.gz hosts_apmc %s@%s:/tmp > /dev/null",
	      login_ssh, "localhost");
      if (system(buf))
	{
	  fprintf(stderr, "Unable to find or upload tarballs.\n");
	  exit(127);
	}
      for (i = 0; argv[i] != NULL; i++)
	{
	  if (!strcmp("$$HOSTNAME$$", argv[i]))
	    {

	      argv[i] = strdup("localhost");
	      sprintf(buf, argv[i+1], current_path_len, login_ssh, nice_level,
		      arity, n_workers);
	      argv[i+1] = buf;
	    }
	}
      execvp(argv[0], argv);
      exit(127);
    }
  worker_pid = pid;
  close(fd_in[1]);
  close(fd_out[0]);
  return 0;
}

static int	read_stdin(void)
{
  int		n_read;
  char		buf[25];

  ioctl(STDIN_FILENO, FIONREAD, &n_read);
  if (n_read < 4) // not enough data to read
    return 0;
  memset(buf, 0, 25);
  read(STDIN_FILENO, buf, 4);
  if (!strcmp("KILL", buf))
    return 42;
  return 0;
}


static void	read_child(long int *path_ok, long int *path_ko)
{
  int		n_read;
  char		buf[25];
  long int	n_ok = -1;
  long int	n_ko = -1;

  ioctl(istream, FIONREAD, &n_read);
  if (n_read < 20) // not enough data to read
    return;
  while (n_read >= 20)
    {
      memset(buf, 0, 25);
      read(istream, buf, 20);
      if (sscanf(buf, "KO:%li", &n_ko))
	*path_ko += n_ko;
      if (sscanf(buf, "OK:%li", &n_ok))
	*path_ok += n_ok;
      if (n_ok < 0 && n_ko < 0)
	fprintf(stderr, "Corrupted data\n"); // FIXME : bad formated data
      n_read -= 20;
    }
}

static void generate_c_code(char *model_file,
			    char *property_file,
			    struct compiler *comp)
{
  FILE *f;

  clean_PMFILE();
  PMFILE = (struct pmfile *)calloc(1, sizeof(struct pmfile));

  if(LTL)
    free_LTL();

  rm_in = fopen( model_file, "r");
  if(!rm_in || rm_parse() )
    {
      if(!rm_in)
	perror(model_file);
      else
	fprintf(stderr, "Parse error in %s, line %d", model_file, rm_lineno);
      exit(-1);
    }
  fclose( rm_in );

  ltl_in = fopen( property_file, "r");
  if(!ltl_in || ltl_parse() )
    {
      if(!ltl_in)
	perror(property_file);
      else
	fprintf(stderr, "Parse error in %s, line %d", property_file, ltl_lineno);
      exit(-1);
    }
  fclose(ltl_in);
  /* FIXME
  do {
    current_code_id += (rand()%0xffffff) + 1;
  } while(current_code_id == 0);
  */
  f = fopen(CODE_SOURCE, "w");
  switch (generate_code_with_compiler(f, LTL, PMFILE, comp))
    {
    case 0:
      break;
    case -1:
      fprintf(stderr, "Error in %s, while generating code with strategy %s",
	      model_file, comp->name);
      exit(-1);
    case -2:
      fprintf(stderr, "Error in %s, while generating code", property_file);
      exit(-1);
    default:
      fprintf(stderr, "Internal error in generate_code_with_compiler : unexpected return code");
      exit(-1);
    }
  fclose(f);
  f = NULL;
}

static struct compiler *verify_strategy(char *strategy)
{
  struct compiler *comp;

  if((comp = get_compiler_from_name(strategy)) == NULL)
    {
      fprintf(stderr, "Unable to find a compiler strategy with name %s choose between\n",
	      strategy);
      comp = get_compiler_from_name(NULL);
      for(comp = get_compiler_from_name(NULL); comp; comp = comp->next)
	fprintf(stderr, "     \"%s\"\n", comp->name);
      exit(-1);
    }
  return comp;
}

static void print_usage(char ** argv)
{
  fprintf(stderr, "usage: %s property_file model_file strategy_name", argv[0]);
  fprintf(stderr, "path_len nbpath login_ssh nice_level arity n_workers\n");
  exit(-1);
}

int main(int argc, char *argv[])
{
  struct compiler *comp;
  char *property_file;
  char *model_file;
  int nbpath;
  struct timeval tv;
  int begin;
  int t1, t2;
  double proba;
  char is_killed = 0;

  if(argc != 10)
    print_usage(argv);
  signal(SIGPIPE, SIG_IGN);
  begin = time(NULL);
  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);
  init_library_apmc();
  property_file = argv[1];
  model_file    = argv[2];
  current_path_len = strtol(argv[4], NULL, 0);
  nbpath           = strtol(argv[5], NULL, 0);
  login_ssh = argv[6];
  nice_level = argv[7];
  arity = argv[8];
  n_workers = argv[9];

  comp = verify_strategy(argv[3]);
  generate_c_code(model_file, property_file, comp);

  system("(cd worker; make dist > /dev/null)");

  create_child(current_path_len);
  current_job_false = current_job_true = 0;
  t1 = time(NULL);
  while(current_job_true + current_job_false < nbpath)
    {
      fd_set all_fd;
      long int ok = 0;
      long int ko = 0;
      struct timeval timeout;
      timeout.tv_sec = 2 * TIMEWAIT;
      timeout.tv_usec = 0;
      FD_ZERO(&all_fd);
      FD_SET(istream, &all_fd);
      FD_SET(STDIN_FILENO, &all_fd);
      select(FD_SETSIZE, &all_fd, NULL, NULL, &timeout);
      if (FD_ISSET(istream, &all_fd))
	read_child(&ok, &ko);
      if (FD_ISSET(STDIN_FILENO, &all_fd))
	if (read_stdin() == 42)
	  {
	    is_killed = 1;
	    break;
	  }
      current_job_true += ok;
      current_job_false += ko;
      t2 = time(NULL);
      if (t2 - t1 > 4)
	{
	  t1 = t2;
	  fprintf(stderr, "ok:%ld\tko:%ld\n", current_job_true, current_job_false);
	}
      if (!current_job_true && !current_job_false && t2 - begin > MAX_START_TIME)
	{
	  fprintf(stderr,
		  "No data during %i seconds. An error is certainly present.\n",
		  MAX_START_TIME);
	  is_killed = 1;
	  break;
	}
      sleep(TIMEWAIT);
      write(ostream, "PING", 4);
    }
  write(ostream, "KILL", 4);
  begin = time(NULL) - begin;
  proba = current_job_true / ((double) (current_job_true + current_job_false));
  fprintf(is_killed ? stderr : stdout, "***ok:%ld\tko:%ld\tin %i seconds\tproba:%0.10lf***\n",
	 current_job_true, current_job_false, begin, proba);
  close(ostream);
  kill(pid, SIGKILL);
  return 0;
}
