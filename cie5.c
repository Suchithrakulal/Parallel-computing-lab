#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int data[4] = {1, 2, 3, 4};  // Sample input array at process 0
    int recv_num;                // Each process receives one number
    int squared;                 // Squared result
    int result[4];               // Gathered result at process 0

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    if (size != 4) {
        if (rank == 0) {
            printf("This program requires exactly 4 processes.\n");
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Scatter one element to each process
    MPI_Scatter(data, 1, MPI_INT, &recv_num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process squares its received number
    squared = recv_num * recv_num;
    printf("Process %d got %d squared = %d\n", rank, recv_num, squared);
    fflush(stdout);

    // Gather squared results back to process 0
    MPI_Gather(&squared, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered result at Process 0: [");
        for (int i = 0; i < 4; i++) {
            printf("%d", result[i]);
            if (i < 3) printf(", ");
        }
        printf("]\n");
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}
