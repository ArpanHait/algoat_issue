import algoat
import numpy as np
import time

def process_sensor_data():
    print("--- Algoat Realistic IoT Sensor Processing Example ---")
    print("Simulating a massive IoT pipeline ingesting 100 Million boolean flags...")

    # 1. Generate realistic IoT sensor failure flags (0 or 1)
    # Using np.random.choice to create a massive boolean array
    num_sensors = 100_000_000
    sensor_flags = np.random.choice([False, True], size=num_sensors, p=[0.95, 0.05])

    print(f"Generated {num_sensors:,} boolean sensor readings.")
    print("Sorting data to isolate failed sensors for downstream analysis...")

    # 2. NumPy baseline
    start_np = time.time()
    np_sorted = np.sort(sensor_flags)
    end_np = time.time()
    np_duration = end_np - start_np

    # 3. Algoat Optimized O(N) Processing
    start_algoat = time.time()
    # algoat automatically recognizes the boolean dtype and routes it to the branchless O(N) backend
    algoat_sorted = algoat.sort(sensor_flags)
    end_algoat = time.time()
    algoat_duration = end_algoat - start_algoat

    print(f"NumPy sort time : {np_duration:.4f} seconds")
    print(f"Algoat sort time: {algoat_duration:.4f} seconds")

    speedup = np_duration / algoat_duration if algoat_duration > 0 else float('inf')
    print(f"Algoat Speedup  : {speedup:.1f}x Faster\n")

    print("The O(N) counting phase drastically reduced the bottleneck, allowing real-time alerting!")

if __name__ == "__main__":
    process_sensor_data()
