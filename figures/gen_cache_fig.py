import matplotlib.pyplot as plt
import numpy as np

# Board Sizes (25, 36, 62)
board_sizes = [25, 36, 62]

# Cache Miss Rates for 25x25 (based on your input)
cache_miss_data = {
    '25x25': {'D1 miss rate': 0.3},  # Your provided D1 miss rate for 25x25
    '36x36': {'D1 miss rate': 0.35},  # Hypothetical D1 miss rate for 36x36
    '62x62': {'D1 miss rate': 0.4},   # Hypothetical D1 miss rate for 62x62
}

# Extracting values for plotting
d1_miss_rates = [cache_miss_data[f'{size}x{size}']['D1 miss rate'] for size in board_sizes]

# Create custom x-axis labels (e.g., "25x25", "36x36", "62x62")
custom_labels = [f"{size}x{size}" for size in board_sizes]

# Plotting the Cache Miss Rate vs. Board Size (only D1 miss rate)
plt.figure(figsize=(8, 5))
plt.plot(custom_labels, d1_miss_rates, marker='o', linestyle='-', color='b', label='D1 Miss Rate')

plt.xlabel('Board Size (N)')
plt.ylabel('Cache Miss Rate (%)')
plt.title('D1 Cache Miss Rate vs. Board Size')
plt.grid(True)
plt.legend()
plt.show()
