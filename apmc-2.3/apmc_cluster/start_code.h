#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include "apmcd.h"

#define new(a)  (a*)calloc(1, sizeof(a))

static unsigned int get_random(unsigned int min, unsigned int max)
{
  max++;
  return min + (unsigned int)( (double)(max-min)*rand()/(RAND_MAX+(double)min));
}

static double probability()
{
  double r = (double)((unsigned int)-2);
  double R = get_random(0, (unsigned int)-2);
  r = ((double)R) / r;
  return r;
}

typedef struct conf {
  int *values;
#ifdef SHOW_STATES
  char *name;
#endif
  struct conf *next;
  struct conf *prev;
} conf;

typedef struct path {
  conf * first;
  conf * last;
  conf *actual;
} path;

typedef int (*tester_t)(const conf *);

static int until(tester_t left, tester_t right, const conf *c)
{
  int cond;

  if(!c) return 0;

  cond = right(c);
  if (cond)
    return 1;
  cond=left(c);
  if (!cond)
    return 0;
  if(!c->next)
    return 0;
  cond=right(c->next);
  if (cond)
    return 1;
  return until(left, right, c->next);
}

static int next(tester_t w, const conf *c)
{
  if(!c) return 0;
  if(!c->next) return 0;
  return w(c->next);
}
