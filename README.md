# Algoat

Algoat is a complete C++20 algorithm library with smart fallback and algorithm dispatch based on data profiles and runtime configuration.

## Features

- **Sorting Algorithms**: Insertion Sort, Quick Sort, Merge Sort, Heap Sort.
- **Searching Algorithms**: Linear Search, Binary Search, Interpolation Search.
- **Smart Dispatching**: Automatically analyzes data to pick the best algorithm (e.g., Insertion Sort for small arrays, Merge Sort for nearly sorted arrays).
- **Runtime Configuration**: Allows overriding the algorithm using JSON configuration.
- **C++20 Concepts**: Fully templated using standard ranges and concepts.

## Build Instructions

Algoat requires a C++20 compliant compiler and CMake 3.21+.

```bash
cmake --preset release
cmake --build build/release
```

To run tests:
```bash
cmake --preset debug
cmake --build build/debug
ctest --test-dir build/debug
```

To run the example:
```bash
build/debug/examples/basic_usage
```

## Usage Example

```cpp
#include <algoat/algoat.hpp>
#include <iostream>
#include <vector>
#include <span>

int main() {
    std::vector<int> data = {42, 7, 19, 100, 3, 55, 21};
    
    // Automatically selects the best sorting algorithm
    algoat::sort(std::span{data});
    
    // Automatically selects the best searching algorithm
    auto res = algoat::search(std::span{data}, 19);
    if (res) {
        std::cout << "Found 19 at index " << *res << "\n";
    }

    return 0;
}
```

## Architecture

Algoat uses a Registry and Dispatcher pattern. Algorithms are registered using a `std::variant` to avoid vtable overhead. The `Dispatcher` dynamically analyzes incoming data using `DataTraits` (size, sortedness ratio) and selects an optimal algorithm if one is not explicitly configured via `AlgoConfig`.
