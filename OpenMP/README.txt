Taller 1

es un conjunto de archivos relacionados con el método del trapecio para aproximar la integral de una función en un intervalo dado. La carpeta "OpenMP" contiene dos archivos, el archivo original "trapezAreaSimple.c" y el archivo paralelizado "omp_trapezAreaSimple.C".

El archivo paralelizado utiliza la biblioteca OpenMP para asignar diferentes subintervalos a diferentes hilos y realizar el cálculo de la suma de la función en cada subintervalo. Los resultados parciales se suman correctamente para obtener el valor total de la integral.

Para compilar el archivo fuente "trapezAreaSimple.C" en Guane, se utiliza el comando "gcc -fopenmp trapezAreaSimple.c -o trapecio -lm", que compila el código con soporte para OpenMP, enlaza la biblioteca matemática estándar y genera un archivo ejecutable llamado "trapecio".

Para ejecutar el archivo ejecutable generado, se utiliza el comando "./ trapecio". Estos mismos comandos se utilizan para compilar y ejecutar el archivo paralelizado "omp_trapezAreaSimple.c".

Para compilar el archivo en una máquina personal, se puede utilizar un compilador de archivos .C como Dev C++. Después de compilar el archivo "omp_trapezAreaSimple.c", se pueden obtener los resultados en un archivo de salida como "output_trapezAreaSimple.txt".