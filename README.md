# Clustering-colloids
**Clustering-colloids** provides a straightforward method to perform clustering analysis, especially for colloidal systems. 
## Compiling using Makefile
* Use _clustering/Makefile_ to compile the code. In the terminal, simply type  
  ```
  make
  ```  
  to compile the *c files stored in _clustering/src/_ and then create the executable file _clustering-colloids_. 

* To remove the objective and executable files, type
  ```
  make clean
  ```
## Usage
Make sure the input file, _config.xyz_, and the executable file are placed in the same directory. In the terminal, change the path to this directory, and then type
```
./clustering-colloids <N_mol> <N_snapshots> <box_X> <box_Y> <box_Z> <rcut> [M]
```
where N\_mol is the number of molecules (particles) in _config.xyz_, N\_snapshots is the total number of snapshots in _config.xyz_, box_X/Y/Z is the size of the simulation box in the X/Y/Z coordinate, rcut is the cut-off radius, and M represents the index of the first snapshot that is taken into consideration.  
The angle brackets <> indicate the argument is required, and the square brackets [] mean that the argument is optional and has a default choice.  
By default, M = "N_snapshots/2".  
To analyze the clustering behavior from the beginning of the input file, set M = 0.
## Input file
The only input file is _config.xyz_, which follows [the xyz file formt](https://en.wikipedia.org/wiki/XYZ_file_format). **Clustering-colloid** loads snapshots of colloidal particles from _config.xyz_, and then computes clustering behavior in each of the snapshots.
## Output files
There are two output files, namely _largestCluster.dat_ and _cluster<rc>.dat_. 
In _largestCluster.dat_, the size of the largest cluster for the i-th snapshot is written. Its time-average can be found in the last two lines of the file.
In _cluster<rc>.dat_, the weighted distribution of cluster size, _nP(n)_, is stored, where _P(n)_ is the probability that a randomly selected cluster consists of _n_ particles. Here, <rc> represents the value of _rc_ up to the 5th decimal place. For example, if rc = 1.12, then the corresponding file name is cluster1.12000.dat.
## Cluster definition
As a typical definition of a cluster in colloidal systems, a cluster is defined as a set of particles that are mutually ''bonded'', where two particles are regarded to be ''bonded'' if their distance is less than a cut-off radius, rcut.
