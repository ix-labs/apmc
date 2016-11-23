#include "apmcd.h"
 
int *getdepth_apmcd_1_svc(struct svc_req *svr)
{
  static int result;
  result = MYDEPTH;
  return &result;
}

void *setdepth_apmcd_1_svc(int d, struct svc_req *svr)
{
  static int result;
  MYDEPTH=d;
  return (void*)&result;
}

connectStatus_t *connect_apmcd_1_svc(char *hostname, struct svc_req *svr)
{
  static connectStatus_t status;
  ADDM_DECLARE(message);
  int i;

  addm_init(message);
  status.message = message;
  status.err = Success;

  for(i = 0; i < NBSUBS; i++)
    if (subs[i] == NULL)
      {
	subs[i] = clnt_create(hostname, APMCD_PROG, APMCD_VER, "tcp");
	
	if( subs[i] == NULL )
	  {
	    status.err = FatalError;
	    addm(message, "Unable to connect %s as child %d : %s",
		 hostname, i, clnt_spcreateerror(hostname));
	  }
	else
	  {
	    void *r;
	    
	    r = setdepth_apmcd_1(MYDEPTH+1, subs[i]);
	    if( r == NULL )
	      {
		status.err = FatalError;
		addm(message, "Child %d (%s) refuses to set its depth: %s",
		     i, hostname, clnt_sperror(subs[i], hostname));
		subs[i] = NULL;
	      }
	    else
	      addm(message, "Subdaemon %d = %s : ok", i, hostname);
	  }
	break;
      }

  if( i == NBSUBS )
    {
      status.err = FatalError;
      addm(message, "Unable to add another child : %d children already",
	   NBSUBS);
    }

  return &status;
}
