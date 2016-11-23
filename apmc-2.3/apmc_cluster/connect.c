#include <stdlib.h>
#include "apmcd.h"

static void usage(char *p)
{
  printf("Usage : %s <parent> [to] <child>\n", p);
  exit(1);
}

static CLIENT *clnt;
static connectStatus_t *cs;
 
static void freecs(void)
{
  if(cs)
    clnt_freeres(clnt, (xdrproc_t)xdr_connectStatus_t, (char*)cs);

  if(clnt)
    clnt_destroy(clnt);
}

static void tree_connect(char *parent, char *child)
{
  clnt = clnt_create(parent, APMCD_PROG, APMCD_VER, "tcp");
  if(clnt == NULL)
    {
      clnt_pcreateerror(parent);
      exit(1);
    }

  atexit(freecs);

  cs = connect_apmcd_1(child, clnt);

  if( !cs )
    {
      clnt_perror(clnt, parent);
      exit(2);
    }

  if( cs->err == FatalError )
    {
      fprintf(stderr, "Unable to connect %s to %s : %s\n",
	      parent, child, cs->message);
      exit(3);
    }

  printf("%s -> %s : ok\n", parent, child);
  exit(0);
}

int main(int argc, char *argv[])
{
  if( argc == 4 &&
      !(strcmp(argv[2], "to")) )
    tree_connect(argv[1], argv[3]);
  else if (argc == 3)
    tree_connect(argv[1], argv[2]);
  else
    usage(argv[0]);

  return 0;
}
