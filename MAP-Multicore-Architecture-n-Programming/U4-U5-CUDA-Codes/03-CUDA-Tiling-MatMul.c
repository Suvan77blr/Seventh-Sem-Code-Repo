#define TILE_WIDTH 16


__global__
void Tiling_MatrixMul(float* Md, float* Nd, float* Pd, int width) {

    // Shared memory tiles.
    __shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
    __shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

    // Thread and block indices.
    int tx = threadIdx.x, ty = threadIdx.y;
    int bx = blockIdx.x, by = blockIdx.y;

    // Global row and column this thread computes.
    int row = by * TILE_WIDTH + ty;     // by * blockDim.y + ty;
    int col = bx * TILE_WIDTH + tx;     // bx * blockDim.x + tx;

    float pValue = 0.0f;

    // Looping over the tiles.
    for(int m=0; m<width; m++) {
        
        // Load the tiles into the shared memory.
        Mds[ty][tx] = Md[row * width + (m * TILE_WIDTH + tx)];
        Nds[ty][tx] = Nd[row * width + (m * TILE_WIDTH + tx)];

        // Synchronise to ensure that all the tiles are loaded.
        __syncthreads();

        // Compute the partial dot product.
        for(int k=0; k<TILE_WIDTH; k++) {
            pValue += Mds[ty][k] * Nds[k][tx];
        }

        // Synchronise threads before loading the next tile.
        __syncthreads();
    }

    // Writing the result to the global memory.
    Pd[row*width + col] = pValue;
}