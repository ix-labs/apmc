#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <errno.h>
#include "apmcd.h"

stopStatus_t *stop_program_1_svc(programId_t pid,
				 struct svc_req *req)
{
  static stopStatus_t status;
  ADDM_DECLARE(message);
  int i, j;
  int error = 0;
  struct stopStatus_t *ss;

  addm_init(message);
  status.message = message;

  status.err = Success;
  if( running_pid != pid )
    {
      status.err = FatalError;
      addm(message, "Could not Stop non-running program %d : %d is running",
	   pid, running_pid);
      return &status;
    }

  for(i = 0; i < NBSONS; i++)
    {
      if( kill(sons[i], SIGTERM) == -1 )
	{
	  error++;
	  addm(message, 
	       "Unix Error %s while killing son %d with SIGTERM",
	       strerror(errno), i);
	}
    }

  j = 0;
  do {
    for(i = 0; i < NBSONS; i++)
      if( sons[i] != -1 )
	break;
    if( i < NBSONS )
      pause();
    j++;
  } while((i != NBSONS) && (j < NBSONS));

  for(i = 0; i < NBSONS; i++)
    if( sons[i] != -1 )
      break;
  
  if( i != NBSONS )
    {
      error++;
      addm(message, "Child %d(%d) didn't die with TERM signal", 
	   i, sons[i]);
    }

  if(error == 0)
    {
      status.err = NonFatalError;
      running_pid = 0;
    }
  else
    status.err = FatalError;

  for(i = 0; i < NBSUBS; i++)
    if( subs[i] )
      {
	ss = stop_program_1(pid, subs[i]);

	if(!ss)
	  {
	    error++;
	    addm(message, "Unable to forward stop to sub daemon %d: %s",
		 i, clnt_sperror(subs[i], ""));
	    subs[i] = NULL;
	    continue;
	  }

	if( ss->err != Success )
	  error++;

	addm(message,
	     "Message from my subdaemon %d:\n%s",
	     i, ss->message);
	
	clnt_freeres(subs[i], (xdrproc_t)xdr_stopStatus_t, (char*)ss);
      }

  if(error == 0)
    status.err = Success;
  return &status;
}
