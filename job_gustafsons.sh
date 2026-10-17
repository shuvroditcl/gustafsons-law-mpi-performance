#!/bin/bash
#SBATCH --job-name=ass2_bucket
#SBATCH --ntasks=40
#SBATCH --time=00:15:00
#SBATCH --exclude=ctcp002       # Skip the broken node

module load openmpi
mpic++ -O3 -o assignment2 assignment2.cpp

# Using UCX and disabling broken OpenIB
echo "========== 1 PROCESSOR (10M) =========="
mpirun --mca pml ucx --mca btl ^openib -np 1 ./assignment2 10000000

echo "========== 4 PROCESSORS (40M) ========="
mpirun --mca pml ucx --mca btl ^openib -np 4 ./assignment2 40000000

echo "========== 8 PROCESSORS (80M) ========="
mpirun --mca pml ucx --mca btl ^openib -np 8 ./assignment2 80000000

echo "========== 12 PROCESSORS (120M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 12 ./assignment2 120000000

echo "========== 16 PROCESSORS (160M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 16 ./assignment2 160000000

echo "========== 20 PROCESSORS (200M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 20 ./assignment2 200000000

echo "========== 24 PROCESSORS (240M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 24 ./assignment2 240000000

echo "========== 28 PROCESSORS (280M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 28 ./assignment2 280000000

echo "========== 32 PROCESSORS (320M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 32 ./assignment2 320000000

echo "========== 36 PROCESSORS (360M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 36 ./assignment2 360000000

echo "========== 40 PROCESSORS (400M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 40 ./assignment2 400000000