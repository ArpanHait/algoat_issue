# Algoat Python Examples

This directory contains standalone Python scripts demonstrating how to use the `algoat` library via its zero-copy Python bindings.

## Files

- `basic_usage.py`: Demonstrates basic usage of the smart sorting and searching dispatchers on standard Python lists and tuples.
- `iot_sensor_analysis.py`: Demonstrates a realistic IoT sensor data processing pipeline handling 100 Million boolean flags, showing real-world speedup.
- `benchmark.py`: A comprehensive benchmarking script using `timeit` that pits `algoat` directly against `numpy` for specialized numerics (Boolean, Float16, Complex64).

## Running the Examples

Make sure you have installed the `algoat` Python package first:
```bash
pip install .
```

Then run the examples directly using your Python interpreter:

```bash
# Basic sorting and searching
python examples/python/basic_usage.py

# Run the performance benchmark against NumPy
python examples/python/benchmark.py
```
