#include "header.h"

void skipSnapshots(FILE *stream, unsigned int nMol, unsigned int M, unsigned int nSnapshots)
{
  unsigned int j;
  char dummy[120];

  for( j = 0 ; j < nMol+2 ; ++j){
    if(NULL == fgets(dummy, 120, stream)){
      printf("startSnapshot = %u\nnSnapshots = %u\n", M, nSnapshots);
      printf("Find an exception: startSnapshot > nSnapshots\n");
      printf("Program exiting...\n");
      exit(-1);
    }
  }
  
  return;
}


int readFile(FILE *stream, unsigned int nMol, unsigned int *nSnapshots, 
             unsigned int iSnapshot, double **pos, double *boxSize)
{
  unsigned int i, j;
  char dummy[120];

  for(i = 0; i < 2 ; ++i){
    if(NULL == fgets(dummy, 120, stream)){
      *nSnapshots = iSnapshot;
      return 0;
    }
  }

  for(i = 0; i < nMol ; ++i){
    unsigned int f;

    f = fscanf(stream, "M %lf %lf %lf\n", &pos[i][0], &pos[i][1], &pos[i][2]); //DIM = 3

    for(j = 0; j < DIM; ++j){ //Checking the boxSize setting
      if(boxSize[j] == 0.0 && pos[i][j] != 0.0){
        printf("Wrong setting in boxSize: L[%u] = %lf and r[%u][%u] = %lf!\n", j, boxSize[j], i, j, pos[i][j]);
	printf("Program exiting...\n");
	exit(-1);
      }
    }

    if(f == 0){
      *nSnapshots = iSnapshot;
      return 0;
    }
  }

  return 1;

}
