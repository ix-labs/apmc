#include <signal.h>
#include <math.h>
#include "apmcd.h"

typedef struct {
  unsigned int yes;
  unsigned int no;
  double prob;
  double epsilon;
  char rel;
} result_t;

static int OUT;

static void on_int(int _)
{
  OUT=1;
}

static void add(result_t **yn, int *ynl, yesno_t p, double confidence)
{
  if (p.yes == 0 && p.no == 0)
    return;
  (*yn)[p.idx].yes += p.yes;
  (*yn)[p.idx].no  += p.no;
  (*yn)[p.idx].prob = ((double) (*yn)[p.idx].yes) / ((double) ((*yn)[p.idx].yes + (*yn)[p.idx].no));
  (*yn)[p.idx].epsilon = confidence / sqrt(((double) ((*yn)[p.idx].yes + (*yn)[p.idx].no)));
}

static void usage(char *ar)
{
  fprintf(stderr, "usage: %s <path-to-executable> <len> <total number of paths> [confidence]\n", ar);
  fprintf(stderr, "  apmcd must be running on localhost (and other hosts to have performances\n");
  fprintf(stderr, "  connect should have established connection between apcmds to have performances\n");
  fprintf(stderr, "  executable must be compiled as RPC client\n");
  fprintf(stderr, "  confidence parameter is only needed when testing against a probability\n");
  fprintf(stderr, "  threshold\n");
  exit(1);
}

int main(int argc, char **argv)
{
  char *server;
  launchStatus_t *rl;
  stopStatus_t *rs;
  queryStatus_t *rq;
  threshold_a *rt;
  CLIENT *clnt;
  args_t args;
  unsigned int pid;
  int j;
  char cwd[PATH_MAX];
  int numpath, minpath;
  result_t *yn;
  int ynl;
  threshold_t *thresholds = NULL;
  unsigned int nb_thresholds = 0;
  char all_ok = 0;
  char res;
  char *r;
  static double confidence = 10e-10;


  if (argc != 4 && argc != 5)
    usage(argv[0]);

  server = strdup("localhost");

  clnt = clnt_create(server, APMCD_PROG, APMCD_VER, "tcp");

  if( clnt == (CLIENT*)NULL) {
    clnt_pcreateerror(server);
    exit(1);
  }

  numpath = strtol(argv[3], &r, 0);
  if( *r != 0 )
    {
      fprintf(stderr, "arg 3 `%s' is not a number\n", argv[3]);
      usage(argv[0]);
    }

  if( argc >= 5 )
  {
    confidence = strtod(argv[4], &r);
    if( *r != 0 )
    {
      fprintf(stderr, "arg 4 `%s' is not a number\n", argv[4]);
      usage(argv[0]);
    }
  }

  confidence = 4 * log(2 / confidence);

  args.args_t_len = 1;
  args.args_t_val = (str*)calloc(1, sizeof(str));
  args.args_t_val[0] = strdup(argv[2]);

  getcwd(cwd, PATH_MAX);
  rl = launch_program_1(0, cwd, argv[1], args, clnt);

  if(rl == (launchStatus_t*)NULL)
    {
      clnt_perror(clnt, server);
      exit(1);
    }

  if( rl->err == FatalError )
    {
      fprintf(stderr, "Fatal Error at launch : %s\n", rl->message);
      exit(2);
    }

  if( rl->err == NonFatalError )
    fprintf(stderr, "Non Fatal Error in launch : %s\n", rl->message);

  pid = rl->pid;
  printf("Succes on launching; pid = %d\n", pid);

  printf("got message %s\n", rl->message);

  clnt_freeres(clnt, (xdrproc_t)xdr_launchStatus_t, (char*)rl);

  while (!nb_thresholds)
  {
    rt = get_thresholds_1(clnt);
    if(rt == (threshold_a*)NULL)
    {
      clnt_perror(clnt, server);
      exit(1);
    }
    nb_thresholds = rt->threshold_a_len;
    if (nb_thresholds)
    {
      thresholds = (threshold_t *)malloc (nb_thresholds * sizeof (threshold_t));
      memcpy(thresholds, rt->threshold_a_val, nb_thresholds * sizeof (threshold_t));
      clnt_freeres(clnt, (xdrproc_t)xdr_threshold_a, (char*)rt);
    }
    sleep(1);
  }

  ynl = nb_thresholds;
  yn = (result_t*)realloc(yn, ynl * sizeof(result_t));
  for(j = 0; j < ynl; j++)
  {
    yn[j].yes = 0;
    yn[j].no  = 0;
    yn[j].yes = 0;
    yn[j].no = 0;
    yn[j].prob = 0;
    yn[j].epsilon = 1;
    yn[j].rel = 0;
  }

  minpath = 0;

  signal(SIGINT, on_int);
  while( (!OUT) && (minpath < numpath) && !all_ok)
    {
      yesno_t *p;

      usleep(50000);

      rq = query_program_1(pid, clnt);

      if(rq == (queryStatus_t*)NULL)
	{
	  clnt_perror(clnt, server);
	  exit(1);
	}

      if( rq->err == FatalError )
	{
	  fprintf(stderr, "Fatal Error in query : %s\n", rq->message );
	  exit(2);
	}

      if( rq->err == NonFatalError )
	fprintf(stderr, "Non Fatal Error in query : %s\n", rq->message);
      p = rq->answers.answers_val;

      for(j = 0; j < rq->answers.answers_len; j++)
	  add(&yn, &ynl, p[j], confidence);

      minpath = yn[0].yes + yn[0].no;
      for(j = 1; j < ynl; j++)
	if( yn[j].yes + yn[j].no < minpath )
	  minpath = yn[j].yes + yn[j].no;

      all_ok = 1;
      for (j = 0; j < ynl; j++)
      {
	if (thresholds[j].op) /* We want a relationship with threshold */
	{
	  if (yn[j].prob - yn[j].epsilon > thresholds[j].threshold)
	    yn[j].rel = 1;
	  else if (yn[j].prob + yn[j].epsilon < thresholds[j].threshold)
	    yn[j].rel = 2;
	  if (yn[j].epsilon < 0.001 && fabs(yn[j].prob - thresholds[j].threshold) < yn[j].epsilon)
	    yn[j].rel = 3;
	}
	all_ok = all_ok && yn[j].rel; /* rel is always zero if we don't test with a threshold */
      }

      fprintf(stderr, "\r%7d/%7d", minpath, numpath);

      clnt_freeres(clnt, (xdrproc_t)xdr_queryStatus_t, (char*)rq);
    }

  fprintf(stderr, "\n");

  rs = stop_program_1(pid, clnt);

  for(j = 0; j < ynl; j++)
    {
      if (!thresholds[j].op)
	printf("property %d : %d/%d %g\n", 
	       j, yn[j].yes, yn[j].no, yn[j].prob);
      else
      {
	res = 0;
	if (!yn[j].rel)
	{
	  if (yn[j].prob > thresholds[j].threshold)
	    yn[j].rel = 1;
	  else if (yn[j].prob < thresholds[j].threshold)
	    yn[j].rel = 2;
	  if (fabs(yn[j].prob - thresholds[j].threshold) < 0.001)
	    yn[j].rel = 3;
	}
	if (thresholds[j].op == 1)
	  res = yn[j].rel == 1;
	else if (thresholds[j].op == 2)
	  res = yn[j].rel == 2;
	else if (thresholds[j].op == 3)
	  res = yn[j].rel == 3;
	else if (thresholds[j].op == 4)
	  res = yn[j].rel == 1 || yn[j].rel == 3;
	else if (thresholds[j].op == 5)
	  res = yn[j].rel == 2 || yn[j].rel == 3;
	printf("property %d : %d/%d %s\n", 
	       j, yn[j].yes, yn[j].no, res ? " true" : "false");
      }
    }

  free(yn);

  if(rs == (stopStatus_t*)NULL)
    {
      clnt_perror(clnt, server);
      exit(1);      
    }
  
  if( rs->err == FatalError )
    {
      fprintf(stderr, "Fatal Error on stop : %s\n", rs->message);
      exit(2);
    }
  
  if( rs->err == NonFatalError )
    {
      fprintf(stderr, "Non Fatal Error on stop %s\n", rs->message);
      exit(3);
    }

  clnt_freeres(clnt, (xdrproc_t)xdr_stopStatus_t, (char*)rs);

  printf("stop was a success\n");
  clnt_destroy(clnt);
  exit(0);
}
