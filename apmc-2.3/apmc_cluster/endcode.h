#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include "apmcd.h"

static CLIENT *clnt;

static void on_sigterm(int _)
{
  clnt_destroy( clnt );
  exit(0);  
}

int main(int argc, char *argv[])
{
  int i;
  int path_len;
  yesno_t yns;
  int nbtrue[NB_VERIF_GOAL];
  int nbfalse[NB_VERIF_GOAL];
  void *result;
  int run_time;
  threshold_a athresholds;

  clnt = clnt_create("localhost",  APMCC_PROG, APMCC_VER, "tcp");

  if (clnt == (CLIENT *)NULL) {
   /*
    * Couldn't establish connection with server.
    * Print error message and die.
    */
    
    clnt_pcreateerror("localhost");
    exit(1);
  }

  signal(SIGTERM, on_sigterm);

  if(argc != 2)
    return -1;

  path_len = atoi(argv[1]);

  {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
  }

/*  for(i = 0; i < NB_VERIF_GOAL; i++)
  {*/
    /* FIXME: really ugly cast */
    athresholds.threshold_a_len = NB_VERIF_GOAL;
    athresholds.threshold_a_val = (threshold_t*)tthresholds;
    result = send_thresholds_1(athresholds, clnt);
    if (result == NULL) { 
      /*
       * An error occurred while calling the server.
       * Print error message and die.
       */

    clnt_perror(clnt, "localhost");
    exit(1);
    }
/*  } */

  for(;;)
    {
      run_time = get_random(4, 8);
      run(nbtrue, nbfalse, path_len, run_time);
      for(i = 0; i < NB_VERIF_GOAL; i++)
	{
	  yns.yes = nbtrue[i];
	  yns.no  = nbfalse[i];
	  yns.idx = i;
	  result = add_1(yns, clnt);
	  if (result == NULL) {
	    /*
	     * An error occurred while calling the server.
	     * Print error message and die.
	     */
	    
	    clnt_perror(clnt, "localhost");
	    exit(1);
	  }
	}
    }
  /* not reached */
}
