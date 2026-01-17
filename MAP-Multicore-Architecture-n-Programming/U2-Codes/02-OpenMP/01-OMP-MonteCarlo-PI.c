/*
    OpenMP Program to estimate PI using Monte Carlo method

    Compilation:
    gcc -fopenmp 01-OMP-MonteCarlo-PI.c -o monte_pi -lm
    ./monte_pi
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    long long int n_points = 1e6;
    long long int hits = 0;

    double pi;

    // Threaded section to compute PI.
    #pragma omp parallel \
            default(none) \
            shared(n_points) \
            reduction(+: hits) \
            num_threads(8)
    {
        int tid = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ tid;
        int n_threads = omp_get_num_threads();
        long long int sample_pts_per_th = n_points / n_threads;
        
        /* Last thread handles remainder */
        if (tid == n_threads - 1) {
            sample_pts_per_th += n_points % n_threads;
        }

        long long int local_hits = 0;

        for(long long int i=0; i<sample_pts_per_th; i++) {
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;

            if( ((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5)) < 0.25 ) {
                local_hits++;
            }
        }
        hits += local_hits;
    }

    pi = 4.0 * hits / n_points;
    printf("Estimated PI Value = %.6f\n", pi);
    printf("Total points = %lld\n", n_points);
    printf("Hits = %lld\n", hits);

    return 0;
}