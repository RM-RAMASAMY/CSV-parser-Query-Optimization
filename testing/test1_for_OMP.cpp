#include <iostream>
#include <omp.h>
#include <chrono>

#define N 2000000000UL // Increase to a larger number for better scaling

void withoutOpenMP()
{
    unsigned long long sum = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned long long i = 0; i < N; i++)
    {
        sum += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Without OpenMP: Sum = " << sum << ", Time taken = " << duration.count() << " seconds\n";
}

void withOpenMP()
{
    unsigned long long sum = 0;
    int num_threads = omp_get_max_threads(); // Get max available threads

    auto start = std::chrono::high_resolution_clock::now();

// Use thread-private sum variables to reduce contention
#pragma omp parallel
    {
        unsigned long long local_sum = 0;
#pragma omp for nowait
        for (unsigned long long i = 0; i < N; i++)
        {
            local_sum += i;
        }

#pragma omp critical
        sum += local_sum; // Safely update global sum
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "With OpenMP: Sum = " << sum << ", Time taken = " << duration.count() << " seconds\n";
}

int main()
{
    std::cout << "Performance Test of OpenMP:\n";

    withoutOpenMP(); // Run single-threaded version
    withOpenMP();    // Run multi-threaded version

    return 0;
}
