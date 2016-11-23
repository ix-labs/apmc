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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "path.h"
#include "reactive-modules.h"

struct ltl_expr *LTL = NULL;

void print_path(path *s)
{
  int i;
  conf *c=s->first;

  while(c)
    {
      printf("[");
      for (i=0;i<s->nb_vars;i++)
	printf("%s=%d%s",s->variables[i],c->values[i],i<s->nb_vars-1?", ":"]");
      c=c->next;
      printf("\n");
    }

}

void print_conf(path *p, conf *c)
{
  int i;
  for (i=0;i<p->nb_vars;i++)
    printf("%s=%d\n",p->variables[i],c->values[i]);
}

void free_conf(conf *c)
{
  if(!c) return;
  ifree(c->values);
  icall(free_conf, c->next);
}

void free_path(path *p)
{
  int i;
  for(i = 0; i < p->nb_vars; i++)
    ifree(p->variables[i]);
  ifree(p->variables);
  icall(free_conf, p->first);
}

static char *read_token(int fd)
{
  char c;
  int size=4096;
  char *buf=(char *)calloc(size,sizeof(char));
  int i=0;
  while(read(fd,&c,1)==1)
    {
      if (c==0)
	{
	  free(buf);
	  return NULL;
	}
      buf[i++]=c;
      if (i>=size)
	{
	  size+=4096;
	  buf=(char *)realloc(buf,size);
	}
	
      if (c==']')
	{
	  buf[i]=0;
	  return buf;
	}
    }
  return NULL;
}

static void parse_first_token(char *buf,path *s)
{
  int nb=0;
  char name[1024];
  char *p;
  int i,j;
  conf *c=(conf *)calloc(1,sizeof(conf));
  for(p=buf;*p;p++)
    {
      if (*p=='=')
	nb++;
    }
  s->nb_vars=nb;
  s->variables=(char **)calloc(nb,sizeof(char *));
  c->values=(int *)calloc(nb,sizeof(int));
  p=buf;
  if (*p!='[')
    {
      printf("error : first char is not [\n");
      exit(0);
    }
  p++;
  for (i=0;i<nb;i++)
    {
      j=0;
      if (i!=0)
	p++;
      while(*p!='=')
	name[j++]=*p++;
      name[j]=0;
      s->variables[i]=strdup(name);
      p++;
      c->values[i]=strtol(p,&p,10);
      switch(*p)
	{
	case ',':
	  continue;
	  break;
	case ']':
	  if (i+1!=nb)
	    {
	      printf("error : i!=nb : i=%d nb=%d\n",i,nb);
	      exit(0);
	    }
	  break;
	default:
	  printf("parse error : %s\n",buf);
	  exit(0);
	}
    }
  s->first=s->last=c;
}

static void add_token(char *buf,path *s)
{
  char *p=buf;
  int i,j;
  conf *c=(conf *)calloc(1,sizeof(conf));
  if (*p!='[')
    {
      printf("error : first char is not [\n");
      exit(0);
    }
  p++;
  c->values=(int *)calloc(s->nb_vars,sizeof(int));
  for (i=0;i<s->nb_vars;i++)
    {
      j=0;
      while(*p!='=')p++;
	
      
      p++;
      c->values[i]=strtol(p,&p,10);
      switch(*p)
	{
	case ',':
	  continue;
	  break;
	case ']':
	  if (i+1!=s->nb_vars)
	    {
	      printf("error : i!=nb\n");
	      exit(0);
	    }
	  break;
	default:
	  printf("parse error : %s\n",buf);
	  exit(0);
	}
    }
  s->last->next=c;
  c->prev=s->last;
  s->last=c;
}


path * parsepath_fromfile(int fd)
{
  char *res;
  path *s=(path *)calloc(1,sizeof(path));
  res=read_token(fd);
  parse_first_token(res,s);
  free(res);
  while( (res=read_token(fd)) )
    {
      add_token(res,s);
      free(res);
    }
  return s;
}

