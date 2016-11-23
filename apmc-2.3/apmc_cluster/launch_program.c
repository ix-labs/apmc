#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <errno.h>
#include "apmcd.h"

static GOGOGO=0;

static void do_nothing(int _)
{
  GOGOGO=1;
  return;
}

static void on_child(int s)
{
  pid_t c;
  int status;
  int i;

  do {
    c = waitpid(-1, &status, WNOHANG);

    if( (c == 0) || ( (c==-1) && (errno == ECHILD) ) )
      break;

    if( c == -1 )
      {
	perror("waitpid");
	break;
      }

    for(i = 0; i < NBSONS; i++)
      if(c == sons[i])
	break;

    if( i == NBSONS )
      fprintf(stderr, "unexpected death of another child %d?!?\n", c);
    else
      {
	sons[i] = -1;

	for(i = 0; i < NBSONS; i++)
	  if(sons[i] != -1)
	    break;

	if(i == NBSONS)
	  {
	    free(yesnos);
	    yesnos = NULL;
	    nb_yesnos = 0;
	  }

	  if( WIFEXITED(status) )
	    addm(sondeath_messages,
		 "*son %d exited with exit status %d", i, WEXITSTATUS(status));
	  else if( WIFSIGNALED(status) )
	    addm(sondeath_messages,
		 "*son %d was signaled with signal %d and terminated", i, WTERMSIG(status));
	  else if( WIFSTOPPED(status) )
	    addm(sondeath_messages,
		 "*son %d was stopped with signal %d", i, WSTOPSIG(status));
	  else
	    addm(sondeath_messages,
		 "*son %d was stopped with unknown status", i);
      }
  } while(1);

  signal(SIGCHLD, on_child);
}

launchStatus_t *launch_program_1_svc(programId_t pid, char *wd, 
				     char *path, args_t args, 
				     struct svc_req *req)
{
  static launchStatus_t status;
  ADDM_DECLARE(message);
  char **argv;
  int i, j;
  int error=0;
  struct launchStatus_t *ls;

  status.message = message;
  addm_init(message);

  if( running_pid != 0 )
    {
      status.err = FatalError;
      addm_noendl(message, 
		  "Could not launch a new pogram %s, another (%d) is running on pids ",
		  path, running_pid);
      for(i = 0 ; i < NBSONS; i++)
	addm_noendl(message, "%d ", sons[i]);
      addm(message, "");
      return &status;
    }

  signal(SIGCHLD, on_child);
  signal(SIGUSR1, do_nothing);

  if( pid == 0 )
    running_pid = next_pid++;
  else
    running_pid = pid;

  for(i = 0; i < NBSONS; i++)
    {
      sons[i] = fork();
      switch(sons[i])
	{
	case -1:
	  error++;
	  addm(message, "Unable to fork son number %d : %s", i, strerror(errno));
	  break;

	case 0:
	  
	  chdir(wd);
	  nice(4);
	  argv = (char**)calloc(args.args_t_len+2, sizeof(char*));
	  argv[0] = strdup(path);
	  for(j = 0; j < args.args_t_len; j++)
	    argv[j+1] = strdup(args.args_t_val[j]);
	  argv[j+1] = NULL;
	  if( !GOGOGO ) pause(); /* wait for the parent to have a correct son value */
	  execv(path, argv);
	  perror("unable to launch program");
	  exit(127);

	default:
	  kill(sons[i], SIGUSR1); /* unfreeze the child */
	  addm(message, "Launch %s on child %d", path, i);
	  break;
	}
    }

  for(i = 0; i < NBSUBS; i++)
    if(subs[i])
      {
	ls = launch_program_1(running_pid, wd, path, args, subs[i]);
	if( ls == NULL )
	  {
	    error++;
	    addm(message, "Unable to forward launch to subdaemon %d : %s",
		 i, clnt_sperror(subs[i], ""));
	    subs[i] = NULL;
	    continue;
	  }

	if( ls->err != Success )
	  error++;

	addm(message, "Message from my subdaemon %d:\n%s",
	     i, ls->message);

	clnt_freeres(subs[i], (xdrproc_t)xdr_launchStatus_t, (char*)ls);
      }
  
  if(error > 0)
    status.err = NonFatalError;
  else
    status.err = Success;

  status.pid = running_pid;

  return &status;
}
