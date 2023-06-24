#include <stdio.h>
#include <math.h>
#include <mpi.h>

/* Define the function to be integrated here: */
double f(double x){
  return x*x;
}

/* Program begins */
int main(int argc, char** argv){
  int rank, size, i, n;
  double a, b, h, x, local_sum=0, total_sum;
  double start_time, end_time, elapsed_time;

  MPI_Init(&argc, &argv);  // Inicializaci�n del entorno MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtiene el rango (ID) del proceso
  MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtiene el tama�o del comunicador

  if(rank == 0){
    printf("\nEnter the no. of sub-intervals: ");
    scanf("%d",&n);
    printf("\nEnter the initial limit: ");
    scanf("%lf",&a);
    printf("\nEnter the final limit: ");
    scanf("%lf",&b);
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);  // Env�a el n�mero de subintervalos a todos los procesos
  MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);  // Env�a el l�mite inicial a todos los procesos
  MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);  // Env�a el l�mite final a todos los procesos

  h = fabs(b-a)/n;  // Calcula el tama�o de cada subintervalo

  start_time = MPI_Wtime(); // Obtiene el tiempo de inicio

  // Cada proceso calcula una parte de la suma local
  for(i = rank + 1; i < n; i += size){
    x = a + i*h;
    local_sum = local_sum + f(x);
  }

  MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  // Reduce todas las sumas locales en la suma total, y la env�a al proceso 0

  end_time = MPI_Wtime(); // Obtiene el tiempo de finalizaci�n

  if(rank == 0){
    double integral = (h/2)*(f(a)+f(b)+2*total_sum);  // Calcula la integral utilizando la f�rmula del trapecio
    printf("\nThe integral is: %lf\n", integral);  // Imprime el resultado de la integral

    elapsed_time = end_time - start_time; // Calcula el tiempo transcurrido

    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    /* C�lculo del throughput */
    double throughput = n / elapsed_time; // C�lculo del throughput
    printf("Throughput: %.2f intervals per second\n", throughput);

    /* C�lculo de la escalabilidad */
    double sequential_time = integral; // Tiempo secuencial para comparaci�n
    double parallel_time = elapsed_time; // Tiempo paralelo
    double speedup = sequential_time / parallel_time; // C�lculo del speedup
    double scalability = sequential_time / (parallel_time * size); // C�lculo de la escalabilidad
    printf("Speedup: %.2f\n", speedup);
    printf("Scalability: %.2f\n", scalability);
  }

  MPI_Finalize();  // Finaliza el entorno MPI
  return 0;
}
