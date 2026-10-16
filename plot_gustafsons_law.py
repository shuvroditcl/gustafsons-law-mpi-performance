import matplotlib.pyplot as plt
from google.colab import files

# Exact data from slurm-42160.out
processors = [1, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40]
computation_time = [1.83086, 1.95954, 2.34837, 2.57284, 2.76216, 2.95864, 3.25304, 3.38322, 3.57604, 3.85506, 3.99685]
network_overhead = [0.03254, 0.17676, 0.28818, 0.48508, 0.64956, 0.79384, 0.83999, 1.01552, 1.21417, 1.40938, 1.63776]
total_time = [1.86341, 2.13631, 2.63655, 3.05791, 3.41172, 3.75248, 4.09303, 4.39874, 4.79021, 5.26444, 5.63461]

# Ideal Gustafson's Law assumes total time stays completely flat at the 1-processor baseline
ideal_time = [1.86341] * len(processors)

# Create the plot
plt.figure(figsize=(10, 6))

# Plot the lines
plt.plot(processors, total_time, marker='o', linestyle='-', color='#0044cc', linewidth=2, markersize=8, label='Total Execution Time')
plt.plot(processors, computation_time, marker='s', linestyle='-', color='#27ae60', linewidth=2, markersize=8, label='Computation Time')
plt.plot(processors, network_overhead, marker='^', linestyle='-', color='#e67e22', linewidth=2, markersize=8, label='Network Overhead')
plt.plot(processors, ideal_time, linestyle='--', color='#e74c3c', linewidth=2, label="Ideal Total Time (Gustafson's Law)")

# Formatting
plt.title("Parallel Bucket Sort Weak Scaling (Gustafson's Law)", fontsize=14, fontweight='bold')
plt.xlabel("Number of Processors (p) & Workload", fontsize=12)
plt.ylabel("Time (Seconds)", fontsize=12)

# Set x-axis ticks to match processor counts exactly
plt.xticks(processors)

# Add grid and legend
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(loc='upper left', fontsize=11)

# Adjust layout and save the image inside the Colab environment
filename = 'assignment2_gustafson_graph.png'
plt.tight_layout()
plt.savefig(filename, dpi=300)

# Display the plot in the notebook
plt.show()

# Trigger the download to your local computer
files.download(filename)
