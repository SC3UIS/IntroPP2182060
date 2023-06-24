#include <stdio.h>

// Kernel que realiza la suma en paralelo
__global__ void sum_kernel(int *sum, int num) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index <= num && index > 0) {
        atomicAdd(sum, index);
    }
}

int main() {
    int num = 10;
    int sum = 0;

    // Alocamos memoria en la GPU para la suma
    int *dev_sum;
    cudaMalloc((void **)&dev_sum, sizeof(int));

    // Copiamos la suma desde la memoria de la CPU a la de la GPU
    cudaMemcpy(dev_sum, &sum, sizeof(int), cudaMemcpyHostToDevice);

    // Creamos los eventos para medir el tiempo
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Empezamos a medir el tiempo
    cudaEventRecord(start);

    // Lanzamos el kernel en la GPU
    sum_kernel<<<num + 1, 1>>>(dev_sum, num);

    // Detenemos el tiempo después de que el kernel termine
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    printf("Elapsed time: %f ms\n", milliseconds);
    printf("Throughput: %f operations/ms\n", num / milliseconds);

    // Copiamos la suma desde la memoria de la GPU a la de la CPU
    cudaMemcpy(&sum, dev_sum, sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nSum = %d\n", sum);

    // Liberamos la memoria de la GPU
    cudaFree(dev_sum);

    return 0;
}
