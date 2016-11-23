#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <strings.h>

#include "reactive-modules.h"
#include "apmc.h"
#include "compilers.h"

void free_LTL();
extern FILE *ltl_in;

int ltl_lineno=1;
struct exprlist *LTL = NULL;

int main(int argc, char *argv[])
{
  int i;
  struct compiler *comp;
  FILE *f;

  comp = get_compiler_from_name("sync at compile-time");

  for(i = 1; i < argc; i+=2)
    {
      printf("allocating PMFILE\n");

      PMFILE = (struct pmfile *)calloc(1, sizeof(struct pmfile));

      rm_in = fopen( argv[i], "r");
      if(!rm_in || rm_parse() )
	{
	  if(!rm_in)
	    perror(argv[i]);
	  else
	    fprintf(stderr, "Parse error in %s, line %d", argv[i], 
		    rm_lineno);
	  exit(-1);
	}
      fclose( rm_in );
      
      printf("parsing LTL\n");

      ltl_in = fopen( argv[i+1], "r");
      if(!ltl_in || ltl_parse() )
	{
	  if(!ltl_in)
	    perror( argv[i+1] );
	  else
	    fprintf(stderr, "Parse error in %s, line %d", 
		    argv[i+1], ltl_lineno);
	  exit(-1);
	}
      fclose(ltl_in);
      
      f = fopen("test.c", "w");
      switch (generate_code_with_compiler(f, LTL, PMFILE, comp))
	{
	case 0:
	  break;
	case -1:
	  fprintf(stderr, "Error in %s, while generating code with strategy %s", 
		  argv[i], comp->name);
	  exit(-1);
	case -2:
	  fprintf(stderr, "Error in %s, while generating code", argv[i+1]);
	  exit(-1);
	default:
	  fprintf(stderr, "Internal error in generate_code_with_compiler : unexpected return code");
	  exit(-1);
	}
      fclose(f);

      printf("doing FREE\n");

      f = NULL;
      free_LTL();
      clean_PMFILE();
    }

  return 0;
}
