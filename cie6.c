#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int local_value, reduce_result, allreduce_result;

    MPI_Init(&argc, &argv);                 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    MPI_Comm_size(MPI_COMM_WORLD, &size);   

    local_value = rank;  

    MPI_Reduce(&local_value, &reduce_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Allreduce(&local_value, &allreduce_result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("MPI_Reduce result at Process 0: Sum of ranks = %d\n", reduce_result);
        printf("MPI_Allreduce result at all processes: Sum of ranks = %d\n", allreduce_result);
    }

    MPI_Finalize();  
    return 0;
}
