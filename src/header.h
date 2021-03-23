#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_REQ_ARGS 7
#define N_ARB_ARGS 1

#define DIM 3

#define SQ(a) ((a)*(a))

double min(double a, double b);
double imgDistance(double *rj, double *rk, double* boxSize);
void calClusterSgSnapshot(int ** cluster, double **r, unsigned int nMol,
                       double *boxSize, double rcut);
void calLargestCluster(FILE * stream2, double *clusterStat,
                      double avgLargestClstrSize,
		      unsigned int st, unsigned int nSnapshots, unsigned int nMol);

void outputClusterStat(unsigned int nMol, double rcut, double *clusterStat);

void skipSnapshots(FILE *stream, unsigned int nMol, unsigned int M, unsigned int nSnapshots);
int readFile(FILE * stream, unsigned int nMol, unsigned int *nSnapshots, 
             unsigned int i, double **pos, double *boxSize);
