#include <stdlib.h>

#include "apmcd.h"

void * send_thresholds_1_svc(threshold_a lthresholds, struct svc_req *req)

{
   static int result; /* must be static, and cannot declare a static void... */
   
   nb_thresholds = lthresholds.threshold_a_len;
   if (thresholds)
     free(thresholds);
   thresholds = malloc (nb_thresholds * sizeof (threshold_t));
   memcpy(thresholds, lthresholds.threshold_a_val, nb_thresholds * sizeof (threshold_t));
   thresholds_received = 1;

   return (void*)(&result);
}
