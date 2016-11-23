/* APMC - Approximate Model Checker
 * Copyright (C) 2003 Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
 *
 * This software is free software; you can redistributed it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful, but 
 * WIHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this software; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "double.h"
#include <math.h>

double get_double(char *c)
{
  double x=0.0;
  double exp=1.0;
  for(;*c&&*c!='.';c++)
    {
      x*=10.0;
      x+=(double)(*c-'0');
    }
  if (*c=='.')
    c++;
  for(;*c;c++)
    {
      exp*=10.0;
      x+=(double)(*c-'0')/exp;
    }
  return x;
}

void fprint_double(FILE *f,double d)
{
  int up,down;
  up=(int)floor(d);
  down=(int)((d-floor(d))*1000000.0);
  fprintf(f,"%d.%06d",up,down);
}
