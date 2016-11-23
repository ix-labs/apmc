#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include "apmcd.h"

unsigned int nb_yesnos = 0;
yesno_t     *yesnos    = NULL;

unsigned int nb_thresholds = 0;
threshold_t *thresholds    = NULL;
char thresholds_received = 0;

pid_t sons[NBSONS] = {-1,};
char sondeath_messages[MLEN] = {0,};

programId_t running_pid = 0;
programId_t next_pid = 1;

#define SPLEN 12
int MYDEPTH=0;
static char space[SPLEN];

CLIENT *subs[NBSUBS] = {NULL,};

static char *myself;

void addm_init(char *m)
{
  struct sockaddr_in my;
  int i;

  if( myself == NULL )
    {
      get_myaddress(&my);
      myself = strdup(inet_ntoa(my.sin_addr));
    }
  
  memset(space, 0, SPLEN);
  for(i = 0; (i < SPLEN-2) && (i < MYDEPTH); i++)
    space[i] = ' ';
  if( (i == SPLEN-2) && (MYDEPTH > SPLEN-1) )
    space[i] = '+';

  m[0] = 0;
}

void addm(char *m, const char *format, ...)
{
  va_list ap;
  static char msg[MLEN];
  int l = strlen(m);

  va_start(ap, format);
  vsnprintf(msg, MLEN-l, format, ap);
  va_end(ap);
  if( (l==0) || (m[l-1] == '\n') )
    snprintf(m+l, MLEN-l, "%s%s: %s\n", space, myself, msg);
  else
    snprintf(m+l, MLEN-l, "%s\n", msg);
}

void addm_noendl(char *m, const char *format, ...)
{
  va_list ap;
  static char msg[MLEN];
  int l = strlen(m);

  va_start(ap, format);
  vsnprintf(msg, MLEN-l, format, ap);
  va_end(ap);
  if( (l==0) || (m[l-1] == '\n') )
    snprintf(m+l, MLEN-l, "%s%s: %s", space, myself, msg);
  else
    snprintf(m+l, MLEN-l, "%s", msg);
}
