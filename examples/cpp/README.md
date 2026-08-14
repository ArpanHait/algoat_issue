# Algoat C++ Examples

This directory contains standalone C++ examples demonstrating how to use the `algoat` C++ library natively.

## Files

- `basic_usage.cpp`: Demonstrates basic inclusion, initialization, and usage of the smart sorting and searching dispatchers.
- `physics_simulation_2d.cpp`: Demonstrates a realistic physics simulation use-case involving the high-performance Morton Z-order spatial clustering for 1,000,000 2D complex numbers.

## Building the Examples

If you configured `algoat` with `-DALGOAT_BUILD_EXAMPLES=ON` (which is enabled by default in the `debug` CMake preset), these examples will be built automatically.

```bash
# From the project root
cmake --preset debug
cmake --build build/debug --target basic_usage

# Run it
./build/debug/examples/cpp/basic_usage
```

If you are using `algoat` as an installed system library or via a package manager (like Conan or vcpkg), you can compile this example directly by linking against `algoat::algoat`.
