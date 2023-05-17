#include <stdio.h>
#include <math.h>
#include <mpi.h>

/* Define la función a ser integrada aquí: */
double f(double x){
  return x*x;
}

/* El programa comienza */
int main(int argc, char** argv){
  int rank, size, i, n;
  double a, b, h, x, local_sum=0, total_sum;

  // Inicializar el entorno MPI
  MPI_Init(&argc, &argv);

  // Obtener el rango (ID) de este proceso y el tamaño total (número de procesos)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Solo el proceso 0 solicitará al usuario el número de intervalos y los límites de integración
  if(rank == 0){
    printf("\nEnter the no. of sub-intervals: ");
    scanf("%d",&n);
    printf("\nEnter the initial limit: ");
    scanf("%lf",&a);
    printf("\nEnter the final limit: ");
    scanf("%lf",&b);
  }

  // Enviar el número de intervalos y los límites de integración a todos los procesos
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // Calcular el tamaño del paso h
  h = fabs(b-a)/n;

  // Cada proceso suma un subconjunto de los intervalos
  for(i = rank + 1; i < n; i+=size){
    x = a + i*h;
    local_sum = local_sum + f(x);
  }

  // Reducir todas las sumas parciales en el proceso 0 para obtener la suma total
  MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  // Solo el proceso 0 calcula y muestra la integral
  if(rank == 0){
    double integral = (h/2)*(f(a)+f(b)+2*total_sum);
    printf("\nThe integral is: %lf\n", integral);
  }

  // Finalizar el entorno MPI
  MPI_Finalize();
  return 0;
}