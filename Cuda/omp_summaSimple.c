#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main()
{
    int num = 10, count, sum = 0;
    // The start and end variables return the elapsed clock time
    double start;
    double end;
    start = omp_get_wtime();
    printf("Positive integer: %d ", num);
    
    // omp parallel creates a new team of threads
    #pragma omp parallel for reduction(+:sum)
    // for loop terminates when num is less than count
    for(count = 1; count <= num; ++count)
    {
        sum += count;
    }

    printf("\nSum = %d\n", sum);
    end = omp_get_wtime();
    printf("Work took %lf seconds\n", end - start);
    printf("Throughput: %lf operations/second\n", num / (end - start));

    return 0;
}
