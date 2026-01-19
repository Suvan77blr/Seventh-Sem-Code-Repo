
__global__
void MatrixMulKernel(float* Md, float* Nd, float* Pd, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    float pValue = 0.0f;

    for(int k=0; k<width; k++) {
        pValue += Md[row*width + k] * Nd[k*width + col];
    }

    Pd[row*width + col] = pValue;
}