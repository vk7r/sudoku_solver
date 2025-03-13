import matplotlib.pyplot as plt
import numpy as np

# Updated Board Sizes (25, 36, 62)
board_sizes = [25, 36, 62]  # Board sizes
num_cells = [size**2 for size in board_sizes]  # Total cells (N^2)
execution_times = [38.2, 75.3, 210.7]  # Execution time in ms

# Create custom x-axis labels (e.g., "25x25", "36x36", "62x62")
custom_labels = [f"{size}x{size}" for size in board_sizes]

# Plot Execution Time vs. Board Size
plt.figure(figsize=(8, 5))
plt.plot(board_sizes, execution_times, marker='o', linestyle='-', color='b', label='Execution Time')
plt.xlabel('Board Size (N)')
plt.ylabel('Execution Time (ms)')
plt.title('Execution Time vs. Board Size')
plt.grid(True)
plt.xticks(board_sizes, custom_labels)  # Set custom x-axis labels
plt.legend()
plt.show()
