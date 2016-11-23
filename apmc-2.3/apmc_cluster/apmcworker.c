#include <signal.h>
#include "apmcd.h"

static CLIENT *clnt;

static void on_sigterm(int _)
{
  printf("bye\n");
  clnt_destroy( clnt );
  exit(0);
}

int main(int argc, char **argv)
{
  char *server;
  yesno_t yn;
  void *result;

  if (argc != 2) {
    fprintf(stderr, "usage: %s len\n", argv[0]);
    exit(1);
  }
  
  server = strdup("localhost");

  /*
   * Create client "handle" used for calling MESSAGEPROG 
   * on the server designated on the command line.
   */

  clnt = clnt_create(server,  APMCC_PROG, APMCC_VER, "tcp");

  if (clnt == (CLIENT *)NULL) {
   /*
    * Couldn't establish connection with server.
    * Print error message and die.
    */
    
    clnt_pcreateerror(server);
    exit(1);
  }

  signal(SIGTERM, on_sigterm);

  for(;;)
    {
      /*
       * Compute the new yes/no
       */
      yn.yes = rand() % 12;
      yn.no  = rand() % 12;
      yn.idx = rand() % 12;

      /*
       * Call the remote procedure
       * "printmessage" on the server
       */

      result = add_1(yn, clnt);
      if (result == NULL) {
	/*
	 * An error occurred while calling the server.
	 * Print error message and die.
	 */

	clnt_perror(clnt, server);
	exit(1);
      }

      /* Okay, we successfully called the remote procedure. */
      usleep(rand() % 10000);
    }

}
