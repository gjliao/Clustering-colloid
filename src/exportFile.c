#include "header.h"

void outputClusterStat(unsigned int nMol, double rcut, double *clusterStat)
{
  unsigned int i;
  char fName[120];
  FILE *stream;

  sprintf(fName, "cluster%lf.dat", rcut);
  stream = fopen(fName,"w");

  fprintf(stream,"#clusterSize nCluster\n"); //n nP(n)

  for( i = 0 ; i < nMol+1 ; ++i ){
    fprintf(stream, "%d %.5lf\n", i, clusterStat[i]*i);
  }

  fclose(stream);
}
