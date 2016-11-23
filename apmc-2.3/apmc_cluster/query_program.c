#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "apmcd.h"

queryStatus_t *query_program_1_svc(programId_t pid, struct svc_req *req)
{
  static queryStatus_t status;
  ADDM_DECLARE(message);
  static yesno_t *ans;
  queryStatus_t *sq;
  int i, j;
  int error = 0;

  addm_init(message);
  status.message = message;
  status.answers.answers_len = 0;
  status.answers.answers_val = NULL;

  if(ans)
    {
      free(ans);
      ans = NULL;
    }

  if( pid != running_pid )
    {
      status.err = FatalError;
      addm(message, "%d is not running : %d is running. Last Death messages where:\n%s",
	   pid, running_pid, sondeath_messages);
      addm_init(sondeath_messages);
      return &status;
    }

  for(i = 0; i < NBSUBS; i++)
    if( subs[i] )
      {
	sq = query_program_1(pid, subs[i]);

	if(!sq)
	  {
	    error++;
	    addm(message, "Unable to forward query to sub daemon %d: %s",
		 i, clnt_sperror(subs[i], ""));
	    subs[i] = NULL;
	    continue;
	  }

	if( sq->err != Success )
	  error++;

	addm(message,
	     "Messages from my subdaemon %d:\n%s",
	     i, sq->message);

	if( sq->err != FatalError )
	  {
	    for(j = 0; j < sq->answers.answers_len; j++)
	      add_1_svc( sq->answers.answers_val[j], NULL);
	  }

	clnt_freeres(subs[i], (xdrproc_t)xdr_queryStatus_t, (char*)sq);
      }

  status.err = (error==0)?Success:NonFatalError;
  status.answers.answers_len = nb_yesnos;
  ans = (yesno_t *)calloc(sizeof(yesno_t), nb_yesnos);
  status.answers.answers_val = ans;
  memcpy(ans, yesnos, nb_yesnos * sizeof(yesno_t));

  for(i = 0; i < nb_yesnos; i++)
    {
      yesnos[i].yes = 0;
      yesnos[i].no  = 0;
      yesnos[i].idx = i;
    }

  return &status;
}
