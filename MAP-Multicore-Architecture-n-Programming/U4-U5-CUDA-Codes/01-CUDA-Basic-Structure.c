/*
    Basic Structure of CUDA Program.
*/

#include <stdio.h>
#include <stdlib.h>

// CUDA Kernel function.
void MatrixMulKernel(float* Md, float* Nd, float* Pd, int width);

int main(void) {
    int width = 1000;
    int size = width * width * sizeof(int);

    float *M, *N, *P;   // Host Matrices.
    float *Md, *Nd, *Pd;   // Device Matrices.

    // Allocating Device Memory.
    cudaMalloc( (void**)&Md, size);
    cudaMalloc( (void**)&Nd, size);
    cudaMalloc( (void**)&Pd, size);

    // Copy input from host to device.
    cudaMemcpy(M, Md, size, cudaMemcpyHostToDevice);
    cudaMemcpy(N, Nd, size, cudaMemcpyHostToDevice);

    // Defining the grid and block dimensions.
    dim3 dimBlock(16, 16, 1);
    dim3 dimGrid(width/16, width/16, 1);

    // Kernel Launch.
    MatrixMulKernel<<< dimGrid, dimBlock >>>(Md, Nd, Pd, width);

    // Copying result back to host.
    cudaMemcpy(P, Pd, size, cudaMemcpyDeviceToHost);

    // Freeing device memory.
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);
    
    return 0;
}