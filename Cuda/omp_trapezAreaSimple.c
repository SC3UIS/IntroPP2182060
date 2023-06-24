#include<stdio.h>
#include<math.h>
#include<omp.h> // Esta es la biblioteca para OpenMP

/* Define la función a integrar aquí: */
double f(double x){
  return x*x;
}

/* El programa comienza */
int main(){
  int n, i;
  double a, b, h, x, sum = 0, integral;
  double start_time, end_time, elapsed_time;
  
  /* Pedir al usuario la entrada necesaria */
  printf("\nEnter the no. of sub-intervals: ");
  scanf("%d", &n);
  printf("\nEnter the initial limit: ");
  scanf("%lf", &a);
  printf("\nEnter the final limit: ");
  scanf("%lf", &b);
  
  /* Comenzar el método trapezoidal:*/
  h = fabs(b - a) / n;
  
  start_time = omp_get_wtime(); // Obtener el tiempo de inicio
  
  #pragma omp parallel for shared(sum) private(i, x)
  for(i = 1; i < n; i++){
    x = a + i * h;
    sum = sum + f(x);
  }
  
  integral = (h / 2) * (f(a) + f(b) + 2 * sum);
  
  end_time = omp_get_wtime(); // Obtener el tiempo de finalización
  
  /* Imprimir la respuesta */
  printf("\nThe integral is: %lf\n", integral);
  
  elapsed_time = end_time - start_time; // Calcular el tiempo transcurrido
  
  printf("Elapsed Time: %.6f seconds\n", elapsed_time);
  
  /* Cálculo del throughput */
  double throughput = n / elapsed_time; // Cálculo del throughput
  
  printf("Throughput: %.2f intervals per second\n", throughput);
  
  /* Cálculo de la escalabilidad */
  int num_threads = omp_get_max_threads(); // Obtener el número máximo de hilos utilizados
  double sequential_time = integral; // Tiempo secuencial para comparación
  double parallel_time = elapsed_time; // Tiempo paralelo
  double speedup = sequential_time / parallel_time; // Cálculo del speedup
  double scalability = sequential_time / (parallel_time * num_threads); // Cálculo de la escalabilidad
  
  printf("Speedup: %.2f\n", speedup);
  printf("Scalability: %.2f\n", scalability);
  
  return 0;
}
