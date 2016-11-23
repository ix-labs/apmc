void free_path(path *p)
{
  conf *c, *o = NULL;

  for(c = p->first; c; c = c->next)
    {
      if(o)
	{
	  free(o->values);
	  free(o);
	}
      o = c;
    }
  if(o)
    {
      free(o->values);
      free(o);
    }
  p->first = p->last = NULL;
}

static CLIENT *clnt;


static void on_sigterm(int _)
{
  clnt_destroy( clnt );
  exit(0);  
}

int main(int argc, char *argv[])
{
  int i;
  struct timeval tv;
  path p = { NULL, NULL };
  int path_len;
  yesno_t yns[NB_VERIF_GOAL];
  time_t t1, t0;
  void *result;

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

  for(i = 0 ; i < NB_VERIF_GOAL; i++)
    {
      yns[i].idx = i;
      yns[i].yes = 0;
      yns[i].no  = 0;
    }

  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);

  t1 = t0 = time(NULL);

  init_state(&p);
  append_state(&p, 1);
  for (i = 0; i < path_len; i++)
    append_state(&p, 1);

  fprintf(stderr, "worker entering main loop\n");

  for(;;)
    {
      init_state(&p);
      append_state(&p, 0);
      for(i = 0; i < path_len; i++)
	{
	  atomic_step();
	  append_state(&p, 0);
	  p.actual = p.actual->next;
	}
      for(i = 0; i < NB_VERIF_GOAL; i++)
	{
	  if( VERIF_GOAL[i](p.first) )
	    yns[i].yes++;
	  else
	    yns[i].no++;
	}

      fprintf(stderr, "worker do .\n");

      t1 = time(NULL);
      if( t1 - t0 >= 1 )
	{
	  t1 = t0;
	  for(i = 0; i < NB_VERIF_GOAL; i++)
	    {
	      result = add_1(yns[i], clnt);
	      if (result == NULL) {
		/*
		 * An error occurred while calling the server.
		 * Print error message and die.
		 */

		clnt_perror(clnt, "localhost");
		exit(1);
	      }
	      yns[i].yes = 0;
	      yns[i].no  = 0;
	    }
	}
    }
  /* not reached */
}
