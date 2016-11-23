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
#include "path.h"
#include "proto.h"
#include "double.h"
#include "compilers.h"

#define CODE_SOURCE  "/tmp/amc_gc_code.c"
#define CODE_BINARY  "/tmp/amc_gc_code"
#define COMPILE_CODE "gcc -o "CODE_BINARY" -O3 "CODE_SOURCE

#define MAXFD 1024

static char *code;
static int   codesize;
static int   current_code_id;
static int   current_path_len;
static int   current_job_true;
static int   current_job_false;

static void close_socket(void *p) 
{ 
  close((int)p); 
} 

static void *connected_thread(void *p) 
{ 
  int fd = (int)p; 
  char c; 

  pthread_cleanup_push(close_socket, p); 

  send(fd, code, codesize, MSG_WAITALL); 
  shutdown(fd, 2); 
  recv(fd, &c, 1, 0); 

  pthread_cleanup_pop(1); 
  return NULL; 
} 

static void *connection_listener(void *_)
{
  int fd, acc;
  struct sockaddr_in remote;
  fd_set rfs;
  int sremote;
  pthread_t cid;
  int nbtest;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fcntl(fd, F_SETFL, SO_REUSEADDR) < 0) 
    perror("fcntl"); 
  
  pthread_cleanup_push(close_socket, (void*)fd); 
  
  remote.sin_addr.s_addr = INADDR_ANY;
  remote.sin_port = htons(CODE_PORT);
  remote.sin_family = AF_INET;

  nbtest = 0;
  do
    {
      if( bind(fd, (struct sockaddr*)&remote, sizeof(remote)) < 0)
	{
	  perror("bind");
	  nbtest++;
	  if(nbtest > 100)
	    {
	      close(fd);
	      pthread_kill_other_threads_np();
	      exit(-1);
	    }
	  else
	    sleep(1);
	}
      else
	break;
    }
  while(nbtest < 50);
    
  if( listen(fd, 5) < 0 )
    {
      close(fd);
      pthread_kill_other_threads_np();
      perror("listen");
      exit(-1);
    }
  
  while(1)
    {
      FD_ZERO(&rfs);
      FD_SET(fd, &rfs);
      if(select(fd+1, &rfs, NULL, NULL, NULL) < 0)
	continue;
      sremote = sizeof(remote);
      acc = accept(fd, (struct sockaddr*)&remote, &sremote);
      if(acc < 0)
	{
	  perror("accept");
	  continue;
	}
      pthread_create(&cid, NULL, connected_thread, (void*)acc);
    }

  pthread_cleanup_pop(1);
}

int main(int argc, char *argv[])
{
  int i;
  struct compiler *comp;
  struct sockaddr_in remote;
  char *property_file;
  char *model_file;
  char *strategy;
  struct stat s;
  int fd;
  pthread_t clid;
  FILE *f;
  int nbpath;
  struct timeval tv;
  int nbtest;

  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);

  if(argc != 6)
    {
      fprintf(stderr, "usage: %s property_file model_file strategy_name path_len nbpath\n",
	      argv[0]);
      exit(-1);
    }

  property_file = argv[1];
  model_file    = argv[2];
  strategy      = argv[3];
  current_path_len = strtol(argv[4], NULL, 0);
  nbpath           = strtol(argv[5], NULL, 0);
  
  comp = get_compiler_from_name(strategy);
  if(!comp)
    {
      fprintf(stderr, "Unable to find a compiler strategy with name %s choose between\n", 
	      strategy);
      comp = get_compiler_from_name(NULL);
      for(comp = get_compiler_from_name(NULL); comp; comp = comp->next)
	fprintf(stderr, "     \"%s\"\n", comp->name);
      exit(-1);
    }
  

  PMFILE = (struct pmfile *)calloc(1, sizeof(struct pmfile));

  clean_PMFILE();
  if(LTL)
    free_LTL();
  
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

  do {
    current_code_id += (rand()%0xffffff) + 1;
  } while(current_code_id == 0);
  
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
  
  if( system(COMPILE_CODE) )
    {
      perror(COMPILE_CODE);
      exit(-1);
    }
  
  if( stat(CODE_BINARY, &s) < 0)
    {
      perror("code download stating file");
      exit(-1);
    }
  codesize = s.st_size;
  code = (char*)malloc(s.st_size);
  fd = open(CODE_BINARY, O_RDONLY);
  read(fd, code, codesize);
  close(fd);
  
  pthread_create( &clid, NULL, connection_listener, NULL);
  
  fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(fd < 0)
    {
      perror("socket");
      exit(-1);
    }
  nbtest = 0;

  do {
    bzero(&remote, sizeof(remote));
    remote.sin_addr.s_addr = INADDR_ANY;
    remote.sin_port = htons(JOB_PORT);
    remote.sin_family = AF_INET;
    
    if( bind(fd, (struct sockaddr*)&remote, sizeof(remote)) < 0)
      {
	nbtest++;
	perror("bind udp");
	sleep(1);
      }
    else
      break;
    if(nbtest > 100)
      exit(-1);
  } while(1);
  
  while(current_job_true + current_job_false < nbpath)
    {
      struct job_reply jr;
      struct job_request ja;
      struct sockaddr_in remote;
      int rlen = sizeof(remote);
      int r;
      
      r = recvfrom(fd,&jr, sizeof(jr), 0, (struct sockaddr*)&remote, &rlen);
      
      if(r == sizeof(jr))
	{
	  if( (jr.code_id != current_code_id) ||
	      (jr.path_len != current_path_len) )
	    {
	      ja.code_id = current_code_id;
	      ja.path_len = current_path_len;
	      sendto(fd, &ja, sizeof(ja), 0,
		     (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
	    }
	  else
	    {
	      current_job_true += jr.nbtrue;
	      current_job_false += jr.nbfalse;
	    }
	}
      else
	fprintf(stderr, "malformed message (size %d)!\n", r);

      fprintf(stderr, "%10d/%10d\r", current_job_true, current_job_false);
    }
  close(fd);
  pthread_kill_other_threads_np();

  for(i = 3; i < MAXFD; i++)
    close(i);

  printf("%d\t%d\n", current_job_true, current_job_false);
  return 0;
}
