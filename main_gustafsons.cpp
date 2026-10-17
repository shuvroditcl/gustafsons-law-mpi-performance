#include <iostream>
#include <vector>
#include <cstdlib>
#include <mpi.h>

// Compare function required for C's qsort()
int compare_floats(const void* a, const void* b) {
    float arg1 = *static_cast<const float*>(a);
    float arg2 = *static_cast<const float*>(b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Phase 3 Function: Routes small buckets to large buckets
int empty_small(std::vector<float>& small_bucket, std::vector<int>& numpb,
                std::vector<float>& big_bucket, int num_data_pp) {
    int num_buckets = numpb.size();

    std::vector<int> recvcnt(num_buckets);
    MPI_Alltoall(&numpb[0], 1, MPI_INT, &recvcnt[0], 1, MPI_INT, MPI_COMM_WORLD);

    std::vector<int> recvoff(num_buckets);
    recvoff[0] = 0;
    int num_recv = recvcnt[0];
    for (int n = 1; n < num_buckets; ++n) {
        recvoff[n] = recvoff[n-1] + recvcnt[n-1];
        num_recv += recvcnt[n];
    }

    std::vector<int> sendoff(num_buckets);
    for (int n = 0; n < num_buckets; ++n) {
        sendoff[n] = n * num_data_pp;
    }

    MPI_Alltoallv(&small_bucket[0], &numpb[0], &sendoff[0], MPI_FLOAT,
                  &big_bucket[0], &recvcnt[0], &recvoff[0], MPI_FLOAT, MPI_COMM_WORLD);

    return num_recv;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) std::cout << "Usage: mpirun -np <p> ./assignment2 <array_size>\n";
        MPI_Finalize();
        return 0;
    }

    int n = std::atoi(argv[1]);
    int local_n = n / size;

    // Start the timers
    double start_time = MPI_Wtime();
    double comm_time = 0.0;
    double temp_time;

    // --- PHASE 1: Parallel Initialization ---
    // Every processor generates its own 10 million elements simultaneously!
    std::vector<float> local_array(local_n);
    srand(12345 + rank); // Give each processor a unique random seed
    for (int i = 0; i < local_n; ++i) {
        local_array[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    // --- PHASE 2: Small Bucket Distribution ---
    std::vector<float> small_bucket(size * local_n);
    std::vector<int> numpb(size, 0);

    for (int i = 0; i < local_n; ++i) {
        float val = local_array[i];
        int b = val * size;
        if (b == size) b--;
        small_bucket[b * local_n + numpb[b]] = val;
        numpb[b]++;
    }

    // --- PHASE 3: Put in Large Buckets ---
    std::vector<float> big_bucket(n);

    // Timer around All-to-All network exchange
    temp_time = MPI_Wtime();
    int total_received = empty_small(small_bucket, numpb, big_bucket, local_n);
    comm_time += (MPI_Wtime() - temp_time);

    // --- PHASE 4: Sort and Gather ---
    // 1. Sort the large buckets in parallel using qsort
    qsort(big_bucket.data(), total_received, sizeof(float), compare_floats);

    // Timer around Final Gathering phase
    temp_time = MPI_Wtime();

    // 2. The master needs to know how many items each process is sending back
    std::vector<int> recv_counts(size);
    MPI_Gather(&total_received, 1, MPI_INT, recv_counts.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // 3. Calculate displacements for Gatherv on the master
    std::vector<int> displs(size, 0);
    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            displs[i] = displs[i-1] + recv_counts[i-1];
        }
    }

    // 4. Gather everything back into the master's final array using Gatherv
    std::vector<float> final_sorted_array;
    if (rank == 0) final_sorted_array.resize(n);

    MPI_Gatherv(big_bucket.data(), total_received, MPI_FLOAT,
                final_sorted_array.data(), recv_counts.data(), displs.data(), MPI_FLOAT,
                0, MPI_COMM_WORLD);

    comm_time += (MPI_Wtime() - temp_time);

    // Stop the global timer
    double end_time = MPI_Wtime();

    double total_time = end_time - start_time;
    double computation_time = total_time - comm_time;

    // Output final results from the Master
    if (rank == 0) {
        std::cout << "========================================\n";
        std::cout << " Bucket Sort Completed Successfully!\n";
        std::cout << " Total Elements Sorted : " << n << "\n";
        std::cout << " Number of Processors  : " << size << "\n";
        std::cout << " ---------------------------------------\n";
        std::cout << " Computation Time      : " << computation_time << " seconds\n";
        std::cout << " Network Overhead      : " << comm_time << " seconds\n";
        std::cout << " Total Execution Time  : " << total_time << " seconds\n";
        std::cout << "========================================\n";
    }

    MPI_Finalize();
    return 0;
}