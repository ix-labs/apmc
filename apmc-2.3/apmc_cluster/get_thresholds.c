#include <stdlib.h>
#include <signal.h>

#include "apmcd.h"

threshold_a *get_thresholds_1_svc(struct svc_req *req)
{
  static threshold_a tthresholds;
  int i, j;
  int error = 0;

  if (!thresholds_received)
  {
    tthresholds.threshold_a_len = 0;
    tthresholds.threshold_a_val = NULL;
  }
  tthresholds.threshold_a_len = nb_thresholds;
  tthresholds.threshold_a_val = thresholds;

  return &tthresholds;
}
