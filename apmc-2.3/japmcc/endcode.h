#include <stdio.h>

static void usage(char *ar)
{
  fprintf(stderr, "Usage: %s <k> <npath> <time> [confidence]\n", ar);
  fprintf(stderr, "  k:           length of paths\n");
  fprintf(stderr, "  npath:       number of paths to generate and verify\n");
  fprintf(stderr, "  time:        time interval (in seconds) for interactive display\n");
  fprintf(stderr, "  confidence:  needed for testing against a probability threshold\n");
  exit(1);
}

struct s_result {
  int nbtrue;
  int nbfalse;
  double prob;
  double epsilon;
  char rel;
};

int main(int argc, char *argv[])
{
  int p, max, k, npath, time;
  char *r;
  char all_ok;
  char res;
  double confidence = 10e-10;

  int nbtrue[NB_VERIF_GOAL];
  int nbfalse[NB_VERIF_GOAL];
  struct s_result results[NB_VERIF_GOAL];

  if( argc != 4 && argc != 5 )
    usage(argv[0]);

  k = strtol(argv[1], &r, 0);
  if( *r != 0 )
    {
      fprintf(stderr, "arg 1 `%s' is not a number\n", argv[1]);
      usage(argv[0]);
    }

  npath = strtol(argv[2], &r, 0);
  if( *r != 0 )
    {
      fprintf(stderr, "arg 2 `%s' is not a number\n", argv[2]);
      usage(argv[0]);
    }

  time = strtol(argv[3], &r, 0);
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

  for(p = 0; p < NB_VERIF_GOAL; p++)
  {
    results[p].nbtrue = 0;
    results[p].nbfalse = 0;
    results[p].prob = 0;
    results[p].epsilon = 1;
    results[p].rel = 0;
  }

  for(;;)
    {
      run(nbtrue, nbfalse, k, time);

      for(p = 0; p < NB_VERIF_GOAL; p++)
	{
	  results[p].nbtrue += nbtrue[p];
	  results[p].nbfalse += nbfalse[p];
	  results[p].prob = ((double) results[p].nbtrue) / ((double) (results[p].nbtrue + results[p].nbfalse));
	  results[p].epsilon = confidence / sqrt(((double) results[p].nbtrue + results[p].nbfalse));
	}
      
      fprintf(stderr, "[2J");

      max = 0;
      all_ok = 1;
      for(p = 0; p < NB_VERIF_GOAL; p++)
	{
	  fprintf(stderr, "[%d;1Hgoal %d: %d|%d = %5.3g%%", 
		  p+1, p, results[p].nbtrue, results[p].nbfalse, 
		  100.0*results[p].prob);
	  if( results[p].nbtrue + results[p].nbfalse > max )
	    max = results[p].nbtrue + results[p].nbfalse;
	  if (tthresholds[p].op) /* We want a relationship with threshold */
	  {
	    if (results[p].prob - results[p].epsilon > tthresholds[p].threshold)
	      results[p].rel = 1;
	    else if (results[p].prob + results[p].epsilon < tthresholds[p].threshold)
	      results[p].rel = 2;
	    if (results[p].epsilon < 0.001 && fabs(results[p].prob - tthresholds[p].threshold) < results[p].epsilon)
	      results[p].rel = 3;
	  }
	  all_ok = all_ok && results[p].rel; /* rel is always zero if we don't test with a threshold */
	}
      if(max >= npath || all_ok)
	break;
      fprintf(stderr, "[%d;1HDone %g%%", p+1, 100.0 * (double)max / (double)npath);
    }

  fprintf(stderr, "[2J[1;1H");

  for(p = 0; p < NB_VERIF_GOAL; p++)
    if (!tthresholds[p].op)
      printf("goal %d: %d|%d = %5.3g%%\n", p, results[p].nbtrue, results[p].nbfalse, 100.0*results[p].prob);
    else
    {
      res = 0;
      if (!results[p].rel)
      {
	if (results[p].prob > tthresholds[p].threshold)
	  results[p].rel = 1;
	else if (results[p].prob < tthresholds[p].threshold)
	  results[p].rel = 2;
	if (fabs(results[p].prob - tthresholds[p].threshold) < 0.001)
	  results[p].rel = 3;
      }
      if (tthresholds[p].op == 1)
	res = results[p].rel == 1;
      else if (tthresholds[p].op == 2)
	res = results[p].rel == 2;
      else if (tthresholds[p].op == 3)
	res = results[p].rel == 3;
      else if (tthresholds[p].op == 4)
	res = results[p].rel == 1 || results[p].rel == 3;
      else if (tthresholds[p].op == 5)
	res = results[p].rel == 2 || results[p].rel == 3;
      printf("goal %d: %d|%d =  %s\n", p, results[p].nbtrue, results[p].nbfalse, res ? " true" : "false");
    }

  return 0;
}
