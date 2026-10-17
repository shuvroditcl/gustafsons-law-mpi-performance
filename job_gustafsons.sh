#!/bin/bash
#SBATCH --job-name=gustafsons_bucket
#SBATCH --ntasks=40
#SBATCH --time=00:15:00
#SBATCH --exclude=ctcp002       # Skip the broken node

module load openmpi
mpic++ -O3 -o main_gustafsons main_gustafsons.cpp

# Using UCX and disabling broken OpenIB
echo "========== 1 PROCESSOR (10M) =========="
mpirun --mca pml ucx --mca btl ^openib -np 1 ./main_gustafsons 10000000

echo "========== 4 PROCESSORS (40M) ========="
mpirun --mca pml ucx --mca btl ^openib -np 4 ./main_gustafsons 40000000

echo "========== 8 PROCESSORS (80M) ========="
mpirun --mca pml ucx --mca btl ^openib -np 8 ./main_gustafsons 80000000

echo "========== 12 PROCESSORS (120M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 12 ./main_gustafsons 120000000

echo "========== 16 PROCESSORS (160M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 16 ./main_gustafsons 160000000

echo "========== 20 PROCESSORS (200M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 20 ./main_gustafsons 200000000

echo "========== 24 PROCESSORS (240M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 24 ./main_gustafsons 240000000

echo "========== 28 PROCESSORS (280M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 28 ./main_gustafsons 280000000

echo "========== 32 PROCESSORS (320M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 32 ./main_gustafsons 320000000

echo "========== 36 PROCESSORS (360M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 36 ./main_gustafsons 360000000

echo "========== 40 PROCESSORS (400M) ======="
mpirun --mca pml ucx --mca btl ^openib -np 40 ./main_gustafsons 400000000
