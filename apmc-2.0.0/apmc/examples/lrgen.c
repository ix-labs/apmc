#include <stdlib.h>
#include <stdio.h>

int inc(char *counter,int level,int lim)
{
  if (level>lim-1)
    return 0;
  if (counter[level])
    {
      counter[level]=0;
      return inc(counter,level+1,lim);
    }
  else
    counter[level]=1;
  return 1;
}


int main(int argc,char **argv)
{
  FILE *f;
  int nbphi;
  int cste;
  int i,j;
  char name[1024];
  char *counter;
  char *pcounter;
  int nom;
  int hamd;
  int prem=0;
  int premint=0;
  if (argc<3)
    {
      printf("usage : %s nb_phi constant\n",argv[0]);
      exit(0);
    }
  nbphi=atoi(argv[1]);
  cste=atoi(argv[2]);
  counter=(char *)calloc(nbphi-1,1);
  sprintf(name,"lr%d%d.pm",nbphi,cste);
  f=fopen(name,"w");

  fprintf(f,"probabilistic\n\nconst n=%d;\n",cste);

  //generate constants
  for(i=1;i<nbphi-1;i++)
    {
      fprintf(f,"const n_%d=%d;\n",i,cste-i);
    }
  
  //generate can formulas
  for(i=1;i<=nbphi;i++)
    {
      fprintf(f,"formula can%d = !(",i);
      bzero(counter,nbphi);
      prem=1;
      while(inc(counter,0,nbphi-1))
	{
	  hamd=0;
	  for(j=0;j<nbphi-1;j++)
	    hamd+=counter[j];

	  if (prem)
	    prem=0;
	  else
	    fprintf(f," | ");

	  if (hamd==1)
	    {
	      nom=0;
	      for(j=0;j<nbphi-1;j++)
		{
		  nom++;
		  if (nom==i)
		    nom++;
		  if (counter[j])
		    fprintf(f,"(c%d=n)",nom);
		}
	    }
	  else
	    {
	      fprintf(f,"(");
	      premint=1;
	      nom=0;
	      for(j=0;j<nbphi-1;j++)
		{
		  nom++;
		  if (nom==i)
		    nom++;
		  if (counter[j])
		    {
		      if (premint)
			premint=0;
		      else
			fprintf(f," & ");
		      fprintf(f,"(c%d=n_%d)",nom,hamd-1);
		    }
		}
	      fprintf(f,")");
	    }
	}
      fprintf(f,");\n");
    }

  //generate count formulas
  for(i=1;i<=nbphi;i++)
    {
      fprintf(f,"formula count%d = (p%d!=13) & (p%d!=0);\n",i,i,i);
      fprintf(f,"formula ncount%d = (p%d=13) | (p%d=0);\n",i,i,i);
    }

  //counter module
  fprintf(f,"\nmodule counter\n\n");
  for(i=1;i<=nbphi;i++)
    {
      fprintf(f,"c%d : [0..n];\n",i);
    }

  //generate actions
  for(i=1;i<=nbphi;i++)
    {
      bzero(counter,nbphi);
      do
	{
	  nom=0;
	  fprintf(f,"\t[s%d] can%d ",i,i);
	  //& ncount2 & ncount3 & ncount4 -> (c1'=0);
	  for(j=0;j<nbphi-1;j++)
	    {
	      nom++;
	      if (nom==i)
		nom++;
	      if (counter[j])
		fprintf(f," & count%d ",nom);
	      else
		fprintf(f," & ncount%d ",nom);
	    }
	  fprintf(f," -> (c%d'=0)",i);
	  nom=0;
	  for(j=0;j<nbphi-1;j++)
	    {
	      nom++;
	      if (nom==i)
		nom++;
	      if (counter[j])
		fprintf(f," & (c%d'=c%d+1)",nom,nom);
	    }
	  fprintf(f,";\n");
	}
      while(inc(counter,0,nbphi-1));
    }
  fprintf(f,"\nendmodule\n\n");


  //formula lfree = (p2=0..4,6,11,13);
  //formula rfree = (p4=0..3,5,7,12,13);

  //generate free formulae
  fprintf(f,"formula lfree = (p2=0..4,6,11,13);\n");
  fprintf(f,"formula rfree = (p%d=0..3,5,7,12,13);\n",nbphi);

  fprintf(f,"\n\nmodule phil1\n\n");
  fprintf(f,"p1 : [0..13];\n");
  fprintf(f,"[s1] (p1=0) -> 0.2 : (p1'=0) + 0.8 : (p1'=1);\n"); 
  fprintf(f,"[s1] (p1=1) -> 0.5 : (p1'=2) + 0.5 : (p1'=3);\n"); 
  fprintf(f,"[s1] (p1=2) &  lfree -> (p1'=4);\n");
  fprintf(f,"[s1] (p1=2) & !lfree -> (p1'=2);\n");
  fprintf(f,"[s1] (p1=3) &  rfree -> (p1'=5);\n");
  fprintf(f,"[s1] (p1=3) & !rfree -> (p1'=3);\n");
  fprintf(f,"[s1] (p1=4) &  rfree -> (p1'=8);\n");
  fprintf(f,"[s1] (p1=4) & !rfree -> (p1'=6);\n");
  fprintf(f,"[s1] (p1=5) &  lfree -> (p1'=8);\n");
  fprintf(f,"[s1] (p1=5) & !lfree -> (p1'=7);\n");
  fprintf(f,"[s1] (p1=6)  -> (p1'=1);\n");
  fprintf(f,"[s1] (p1=7)  -> (p1'=1);\n");
  fprintf(f,"[s1] (p1=8)  -> (p1'=9);\n");
  fprintf(f,"[s1] (p1=9)  -> (p1'=10);\n");
  fprintf(f,"[s1] (p1=10) ->  0.5 : (p1'=11) + 0.5: (p1'=12);\n");
  fprintf(f,"[s1] (p1=11) -> (p1'=13);\n");
  fprintf(f,"[s1] (p1=12) -> (p1'=13);\n");
  fprintf(f,"[s1] (p1=13) ->  0.5 : (p1'=0) + 0.5 : (p1'=13);\n");
  fprintf(f,"\nendmodule\n\n");

  for(i=2;i<=nbphi;i++)
    {
      fprintf(f,"module phil%d=phil1 [p1=p%d, p2=p%d, p3=p%d, p4=p%d, s1=s%d] endmodule\n",i,i,(i)%(nbphi)+1,(i+1)%(nbphi)+1,(i+2)%(nbphi)+1,i);
    }
 
  fclose(f);
}
