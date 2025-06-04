// mpicc mpi_node.c
// mpirun -n 4 a.out

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
  int myrank, nprocs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  printf("I am node %d of %d\n", myrank, nprocs);

  MPI_Finalize();
  return 0;
}