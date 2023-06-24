# Comparación de rendimiento: CUDA vs. OpenMP vs. MPI

Trapezoide:

Este repositorio contiene un programa en C que calcula una integral numérica utilizando tres enfoques diferentes: CUDA, OpenMP y MPI. El objetivo es comparar el rendimiento de estos enfoques en términos de velocidad, escalabilidad y throughput.

Sigue las instrucciones en pantalla para ingresar los parámetros necesarios.

Observa los resultados que incluyen la integral calculada, el tiempo transcurrido, el speedup, la escalabilidad y el throughput.

## Resultados obtenidos

A continuación se presentan los resultados obtenidos para diferentes configuraciones:

### CUDA

- Sub-intervalos: 10
- Límite inicial: 5
- Límite final: 7
- Integral: 72.680000
- Tiempo transcurrido: 0.000181 segundos
- Speedup: 401636.38
- Escalabilidad: 1568.89

### OpenMP (OMP)

- Sub-intervalos: 7
- Límite inicial: 5
- Límite final: 10
- Integral: 262.572886
- Tiempo transcurrido: 0.007145 segundos
- Throughput: 979.65 intervalos por segundo
- Speedup: 36747.12
- Escalabilidad: 2296.69

### Message Passing Interface (MPI)

- Sub-intervalos: 7
- Límite inicial: 5
- Límite final: 10
- Integral: 292.091837
- Tiempo transcurrido: 0.000031 segundos
- Throughput: 229376.00 intervalos por segundo
- Speedup: 9571265.31
- Escalabilidad: 9571265.31

## Conclusiones

- En términos de speedup y escalabilidad, CUDA muestra el mejor rendimiento, con un speedup de 401636.38 y una escalabilidad de 1568.89.
- En cuanto al tiempo transcurrido, MPI es la opción más rápida, con un tiempo de solo 0.000031 segundos.
- OMP muestra una buena tasa de rendimiento con un throughput de 979.65 intervalos por segundo.





![WhatsApp Image 2023-06-23 at 7 05 43 PM](https://github.com/SC3UIS/IntroPP2182032/assets/46767951/cb358b7d-f31e-408c-9bca-e84345a6c2c2)
![WhatsApp Image 2023-06-23 at 6 58 27 PM](https://github.com/SC3UIS/IntroPP2182032/assets/46767951/5da6bfd9-4a8f-4104-af97-36ec3e1669e5)
![WhatsApp Image 2023-06-23 at 6 58 02 PM](https://github.com/SC3UIS/IntroPP2182032/assets/46767951/eb7b4b8b-eebb-4008-83f1-5d40984a0407)

Suma:
Los tres programas realizan la misma operación: calcular la suma de los números del 1 al 10. Sin embargo, utilizan diferentes métodos de paralelización y se ejecutan en diferentes tipos de hardware, lo que lleva a diferentes métricas de rendimiento.

CUDA: La versión CUDA del programa se ejecuta en la GPU y tiene un tiempo de ejecución de 0.048192 milisegundos. El throughput, o número de operaciones por milisegundo, es de 207.503326 operations/ms. Este alto throughput es posible gracias a la gran cantidad de núcleos en la GPU que pueden ejecutar operaciones en paralelo.

OpenMP: La versión OpenMP del programa se ejecuta en la CPU, pero utiliza múltiples hilos para paralelizar la operación de suma. Tiene un tiempo de ejecución de 0.003944 segundos (o 3.944 milisegundos), lo cual es más lento que la versión CUDA. Sin embargo, su throughput es considerablemente más alto, con 2535.417856 operaciones por segundo (o 2.535417856 operaciones por milisegundo). Esto puede deberse a que la paralelización a nivel de hilo en la CPU es más eficiente para esta operación de suma en particular que la paralelización a nivel de hilo en la GPU.

MPI: La versión MPI del programa también se ejecuta en la CPU y utiliza múltiples procesos en lugar de hilos. Tiene un tiempo de ejecución secuencial de 0.039565 segundos (o 39.565 milisegundos), que es el más largo de los tres. Su throughput es de 252.749613 operaciones por segundo (o 0.252749613 operaciones por milisegundo), que es el más bajo de los tres. Esto puede deberse a que la creación y sincronización de múltiples procesos en MPI puede ser más costosa en términos de tiempo que el uso de hilos en OpenMP o la ejecución en paralelo en la GPU con CUDA.

En resumen, cada método de paralelización tiene sus ventajas y desventajas dependiendo del hardware disponible y del tipo de operación que se está realizando. En este caso particular, la versión OpenMP del programa parece ofrecer el mejor balance entre tiempo de ejecución y throughput. Sin embargo, para operaciones más complejas o conjuntos de datos más grandes, la versión CUDA podría ser más eficiente gracias a la gran cantidad de núcleos en la GPU.

![WhatsApp Image 2023-06-23 at 11 11 34 PM](https://github.com/SC3UIS/IntroPP2182032/assets/46767951/a53eaad0-738d-4a6a-a88b-13dbc7c8ab65)
![WhatsApp Image 2023-06-23 at 11 20 48 PM](https://github.com/SC3UIS/IntroPP2182032/assets/46767951/ff8d3896-ab0f-4ef8-b413-5bd33c3afa13)
![WhatsApp Image 2023-06-23 at 11 26 27 PM](https://github.com/SC3UIS/IntroPP2182032/assets/46767951/c58f3139-c6c0-49f4-9f29-93abe3d84148)


