**Parallel Computing Performance Visualizer: Gustafson's Law & Weak Scaling**

This repository contains a Python-based data visualization tool designed to analyze the performance, bottlenecks, and scalability of high-performance computing (HPC) applications. Specifically, the script models the weak scaling efficiency of a parallelized Message Passing Interface (MPI) algorithm, evaluating its real-world execution against the theoretical bounds of Gustafson's Law. It provides a clear, high-quality visual breakdown of how distributed computational workloads behave as processor counts and dataset sizes scale simultaneously across a cluster network.

The underlying data processed and plotted by this script originates from batch jobs executed on a SLURM-managed HPC cluster running a parallel Bucket Sort algorithm. The experimental setup maintained a strictly constant computational workload of 10,000,000 array elements per processor. The script visualizes the resulting performance metrics as the system scales from a single processor up to 40 distributed processors collaboratively processing 400 million elements.

Built using Python and the Matplotlib library, the script generates a comprehensive multi-line plot that isolates different phases of parallel execution. It distinctly separates pure mathematical computation time from inter-node network overhead—such as the communication delays caused by heavy collective routing operations like MPI_Alltoallv and MPI_Gatherv. By plotting these independent variables alongside the total execution time, the generated graph reveals the exact thresholds where physical hardware limitations, memory bus contention, and network traffic begin to degrade ideal performance.

A defining feature of this visualization is the inclusion of a theoretical "Ideal" baseline representing perfect weak scaling efficiency under Gustafson's Law. By contrasting the real-world cluster execution data against this perfectly flat ideal trajectory, the script provides definitive visual proof that while localized computation time remains relatively stable, the exponential growth in inter-process network communication serves as the primary bottleneck in distributed systems.

Ultimately, this repository serves as a lightweight, highly adaptable template for developers, researchers, and students looking to visualize cluster performance data, diagnose network bottlenecks, and generate academic-quality charts for their own parallel computing projects.
## Sample Output

![Gustafson's Law Weak Scaling Graph](assignment2_gustafson_graph.png)
