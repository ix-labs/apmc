/*
 * apmcd.x - Specification of remote APMC worker
 */

const MAXARGS = 128;

typedef unsigned int programId_t;

enum error_t {
  Success   = 0,
  FatalError = 1,
  NonFatalError = 2
};

struct launchStatus_t
{
   error_t     err;
   programId_t pid;
   string message<>;
};

struct stopStatus_t 
{
   error_t err;
   string message<>;
};

typedef stopStatus_t connectStatus_t;

struct yesno_t {
  unsigned int idx;
  unsigned int yes;
  unsigned int no;
};

%extern yesno_t *yesnos;
%extern unsigned int nb_yesnos;

struct queryStatus_t
{
   error_t err;
   yesno_t answers<>;
   string message<>;
};

struct threshold_t {
  char op;
  double threshold;
};

%extern threshold_t *thresholds;
%extern unsigned int nb_thresholds;
%extern char thresholds_received;

%#include <sys/types.h>
%#include <unistd.h>
%#define NBSONS 1
%extern programId_t running_pid;
%extern programId_t next_pid;
%extern pid_t sons[NBSONS];
%#define NBSUBS 2
%extern int MYDEPTH;
%extern CLIENT *subs[NBSUBS];
%#define MLEN 4096
%#define ADDM_DECLARE(m) static char m[MLEN]
%extern char sondeath_messages[MLEN];
%extern void addm_init(char *m);
%extern void addm(char *m, const char *format, ...);
%extern void addm_noendl(char *m, const char *format, ...);

typedef string str<>;
typedef str args_t<MAXARGS>;
typedef threshold_t threshold_a<>;

program APMCD_PROG {
  version APMCD_VER {
    launchStatus_t  LAUNCH_PROGRAM(programId_t pid, string wd, string path, args_t args) = 1;
    stopStatus_t    STOP_PROGRAM(programId_t id) = 2 ;
    queryStatus_t   QUERY_PROGRAM(programId_t id) = 3;
    connectStatus_t CONNECT_APMCD(string hostname) = 4;
    int             GETDEPTH_APMCD(void) = 5;
    void            SETDEPTH_APMCD(int d) = 6;
    threshold_a     GET_THRESHOLDS(void) = 7;
  } = 1;          /* version number 1 */
} = 0x21055012;   /* Unique program number -- well, let's hope this is unique enough */

program APMCC_PROG {
  version APMCC_VER {
    void            ADD(yesno_t p) = 1;
    void            SEND_THRESHOLDS(threshold_a lthresholds) = 2;
  } = 1;
} = 0x21044012;

