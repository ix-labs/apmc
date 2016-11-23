#include <stdlib.h>
#include <string.h>

#include "apmcd.h"

void * add_1_svc(yesno_t yn, struct svc_req *req)

{
   static int result; /* must be static, and cannot declare a static void... */
   unsigned int oldnb;
   int i;

   if( nb_yesnos <= yn.idx )
     {
       oldnb = nb_yesnos;
       nb_yesnos = yn.idx+1;
       yesnos = (yesno_t *)realloc(yesnos, nb_yesnos * sizeof(yesno_t));
       for(i = oldnb; i < nb_yesnos; i++)
	 {
	   yesnos[i].yes = 0;
	   yesnos[i].no  = 0;
	   yesnos[i].idx = i;
	 }
     }

   yesnos[yn.idx].idx = yn.idx;
   yesnos[yn.idx].yes += yn.yes;
   yesnos[yn.idx].no  += yn.no;

   return (void*)(&result);
}
