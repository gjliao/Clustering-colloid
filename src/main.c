#include "header.h"

void printUsage(char *exec);
void checkM(unsigned int M, unsigned int nSnapshots);

int main(int argc, char *argv[]){
  unsigned int i, j;
  unsigned int nMol, nSnapshots, M;
  double rcut;
  double **pos; //i:index for molecules, j:index for coordinates
  double *clusterStat;
  int **cluster;
  double boxSize[DIM];

  //handling  command line arguments
  if(argc > N_REQ_ARGS + N_ARB_ARGS ||
     argc < N_REQ_ARGS ){
    printUsage(argv[0]);
  }
  
  nMol = atoi(argv[1]);
  nSnapshots = atoi(argv[2]);

  boxSize[0] = atof(argv[3]);
  boxSize[1] = atof(argv[4]);
  boxSize[2] = atof(argv[5]);
  
  rcut = atof(argv[6]);

  if(argc == N_REQ_ARGS + N_ARB_ARGS)
    M = atoi(argv[7]);
  else
    M = nSnapshots/2;

  checkM(M, nSnapshots);

  //calloc pos
  pos = (double**) calloc(nMol, sizeof(double*));
  for(i = 0 ; i < nMol ; ++i){
    pos[i] = (double*) calloc(DIM, sizeof(double));
  }

  //calloc cluster
  cluster = (int**) calloc(nMol, sizeof(int*));
  for(i = 0 ; i < nMol ; ++i)
    cluster[i] = (int*) calloc(nMol+1, sizeof(int));

  //calloc clusterStat
  clusterStat = (double*) calloc(nMol+1, sizeof(double));

  /***********************************************************************/

  //reading from file
  unsigned int n;  //cluster size
  unsigned int largestClusterSize=0;
  double avgLargestClusterSize=0;
  FILE *stream;  //reading from config.xyz
  FILE *stream2; //writing into largestCluster.dat
  
  stream = fopen("config.xyz", "r");
  stream2 = fopen("largestCluster.dat","w");

  for(i = 0 ; i < nSnapshots ; ++i){
    if(i < M){
      skipSnapshots(stream, nMol, M, nSnapshots);
    }
    else{
      if(i == M){
        fprintf(stream2, "#iSnapshot largest_cluster_size\n");
      }

      //calculate cluster
      if(readFile(stream, nMol, &nSnapshots, i, pos, boxSize)==0)
        break;
      else {
        largestClusterSize=0;
        calClusterSgSnapshot(cluster, pos, nMol, boxSize, rcut);
       
        //compute statistics quantities of clusters
        for( j = 0 ; j < nMol ; ++j){
          n = cluster[j][0];
          if(largestClusterSize < n){
            largestClusterSize = n;
          }
          
          if(n > 0)
            ++clusterStat[n];
        }
        
        avgLargestClusterSize += largestClusterSize;
        fprintf(stream2, "%d %d\n", i, largestClusterSize);
      }
    }
  }
  calLargestCluster(stream2, clusterStat, avgLargestClusterSize, M, nSnapshots, nMol);

  fclose(stream2);
  fclose(stream);

  //output Statistic of Cluster Size
  outputClusterStat(nMol, rcut, clusterStat);

  //free pointers
  for( i = 0 ; i < nMol ; ++i){
    free(pos[i]);
  }
  free(pos);

  for( i = 0 ; i < nMol ; ++i)
    free(cluster[i]);
  free(cluster);

  free(clusterStat);

  return 0;
}

void printUsage(char *exec)
{
  printf("Usage: %s <N_mol> <N_snapshots> <box_X> <box_Y> <box_Z> <rcut> [M]\n", exec);
  printf("M represents the index of the first snapshot that is taken into consideration.\n");
  printf("By default, M = \"N_snapshots/2\".\n");
  printf("To anaylze the clusering behavior from the beginning of the input file, set M = 0.\n");
  exit(1);
}

void checkM(unsigned int M, unsigned int nSnapshots)
{
  if(M >= nSnapshots){
    printf("Error Found!\n");
    printf("The index of the starting snapshot is greater than that of the last snapshot!\n");
    exit(-1);
  }

  return;
}
