#include "header.h"

void merge(int * a, int * b)
{
  unsigned i, na, nb;

  na = a[0];
  nb = b[0];

  for( i = 1 ; i <= nb ; ++i){
    a[na+i] = b[i];
    b[i] = -1;
  }
  a[0] += nb;
  b[0] = 0;
}

void move(int * a, int ** cluster, unsigned int m)
{
  unsigned int i, k;

  ++a[0];
  k = a[0];

  if(a[k] == -1)
    a[k] = m;
  else{
    printf("Error Found in func. \"move\"()!\n");
    printf("Particle %d is replaced by particle %d!\n", a[k], m);
    printf("array size = %d\n", k);
    for(i = 1 ; i <= k; ++i)
      printf("a[%d] = %d\n", i, a[i]);
    exit(-1);
  }
  cluster[m][0] = 0;
  cluster[m][1] = -1;
}

void calClusterSgSnapshot(int ** cluster, double **r, unsigned int nMol,
                       double *boxSize, double rcut)
{
  double rmn;
  int *a;
  unsigned int m, n, i, j;

  for( i = 0 ; i < nMol ; ++i){
    cluster[i][0] = 1;
    cluster[i][1] = i;
    for( j = 2 ; j < nMol+1 ; ++j){
      cluster[i][j] = -1;
    }
  }

  for( m = 0 ; m < nMol ; ++m){
    a = NULL;
    for( i = 0 ; i < m ; ++i){
      for( j = 1 ; j <= cluster[i][0] ; ++j){
        n = cluster[i][j];

        if(n == -1){
          printf("Error Found in func. \"calClusterSgSnapshot\"()!\n");
          printf("Finding a particle with index -1!\n");
          exit(-1);
        }

        rmn = imgDistance(r[m], r[n], boxSize);
        if(rmn  <= rcut*(1+ pow(10,-4))){
          if(a == NULL)
            a = cluster[i];
          else{
            merge(a, cluster[i]);
          }
          break;
        }
      }
    }
    if(a != NULL)
      move(a, cluster, m);
  }

}

void calLargestCluster(FILE * stream2, double *clusterStat,
                      double avgLargestClusterSize,
                      unsigned int st, unsigned int nSnapshots, unsigned int nMol)
{
  unsigned int i;
  double normal_factor=0.0;

  for( i = 0 ; i < nMol+1 ; ++i)
    normal_factor += clusterStat[i];
  for( i = 0 ; i < nMol+1 ; ++i)
    clusterStat[i] /= normal_factor;
  
  avgLargestClusterSize/=(nSnapshots - st);

  fprintf(stream2, "#Average Largest Cluster Size = %lf\n", avgLargestClusterSize);
  fprintf(stream2, "#The relative Size = %lf\n", avgLargestClusterSize/nMol);

}


double imgDistance(double *rj, double *rk, double* boxSize)
{
  unsigned i;
  double r, b;
  double Rjk[DIM], Rjk2=0.0;

  for( i = 0 ; i < DIM ; ++i ){
    r = rj[i] - rk[i];
    b = boxSize[i];
    if(b == 0.0) 
      continue;
    Rjk[i] = r - floor(r/b + 0.5)*b;
    Rjk2 += SQ(Rjk[i]);
  }

  return sqrt(Rjk2);
}
