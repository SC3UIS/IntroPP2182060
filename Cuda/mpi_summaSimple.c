#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>

double get_wall_time() {
 struct timeval time; 
 if (gettimeofday(&time, NULL)) {
  return 0;
 }
 return (double)time.tv_sec + (double)time.tv_usec * .000001;
} 

int main() {
    int num = 10, count, sum = 0, total_sum = 0;
    double start_time, end_time;
    double sequential_time, parallel_time, acceleration;
    start_time = get_wall_time();

    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_sum = 0;

    // Cada proceso MPI calcula una parte del sumatorio
    for (count = rank + 1; count <= num; count += size)
    {
        local_sum += count;
    }

    // Se reduce la suma local de cada proceso en la suma total
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end_time = get_wall_time();

    if (rank == 0)
    {
        printf("Positive integer: %d\n", num);
        printf("Sum = %d\n", total_sum);
        
        sequential_time = end_time - start_time; 
        printf("Sequential Time: %lf seconds\n", sequential_time);
        parallel_time = sequential_time / size;
        printf("Parallel Time: %lf seconds\n", parallel_time); 
        acceleration = sequential_time / parallel_time;
        printf("Acceleration: %lf\n", acceleration);
        printf("Throughput: %lf operations/second\n", num / sequential_time);
    }

    MPI_Finalize();

    return 0;
}
