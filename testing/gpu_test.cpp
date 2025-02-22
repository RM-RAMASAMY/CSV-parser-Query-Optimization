#include <iostream>
#include <cuda_runtime.h>

int main()
{
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);

    std::cout << "GPU Name: " << prop.name << "\n";
    std::cout << "Total CUDA Cores: " << prop.multiProcessorCount * 128 << "\n";
    std::cout << "Streaming Multiprocessors (SMs): " << prop.multiProcessorCount << "\n";
    std::cout << "Max Threads per SM: " << prop.maxThreadsPerMultiProcessor << "\n";
    std::cout << "Max Threads per Block: " << prop.maxThreadsPerBlock << "\n";
    std::cout << "Max Blocks per Grid: " << prop.maxGridSize[0] << "\n";

    return 0;
}
