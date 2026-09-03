# Changelog

All notable changes to **Algoat** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html) and [Conventional Commits](https://www.conventionalcommits.org/).

---

## [0.1.1] - 2026-09-03

### 🚀 Features

- feat(searching): implement sub-linear simd profiler and adaptive binary search @Sambit003 (#43)

### ⚡ Performance Optimizations

- perf(searching): implement branchless binary search and numpy zero-copy search overloads @ArpanHait (#40)

### 🐛 Bug Fixes & Security

- fix(sorting): resolve sort_boolean silent corruption with branchless Lomuto partition @Sambit003 (#47)
- fix(sorting): rectify TimSort natural runs and merge invariants @Sambit003 (#46)
- fix(sorting): implement 3-way fat partitioning to eliminate duplicate key quadratic degradation (#16) @ArpanHait (#42)
- fix(sorting): harden numeric bounds and memory safety in core algorithms @Sambit003 (#36)
- fix(python): isolate GC and list cloning in Python benchmark harness @ArpanHait (#37)
- Fix macOS wheel link failure by removing private CPython bigint APIs @[copilot-swe-agent[bot]](https://github.com/apps/copilot-swe-agent) (#1)
- Fix ubuntu wheel build failure by using a newer manylinux image for cibuildwheel @[copilot-swe-agent[bot]](https://github.com/apps/copilot-swe-agent) (#2)

### 📖 Documentation

- docs: add comprehensive Doxygen documentation, IDE tooltip optimization, and ARCHITECTURE.md @Sambit003 (#3)

### 🩹 Patches & Maintenance

- refactor(sorting): consolidate comparative sorting test harness via TYPED_TEST_SUITE @Sambit003 (#41)
- refactor(build): prune empty translation units from algoat target @Ritesh-Gupta-op (#9)

---

## [0.1.0] - 2026-08-16

### 🚀 Highlights

Algoat is a high-performance C++20 algorithm library with smart dispatch and zero-copy Python bindings. This initial release ships **14 sorting algorithms**, **3 searching algorithms**, and **domain-specific O(N) numerics** that outperform NumPy on specialized data types.

### ✨ Features

#### Sorting Algorithms
- **Classical**: InsertionSort, SelectionSort, BubbleSort, ShellSort (Ciura), CombSort, GnomeSort, CycleSort
- **Divide & Conquer**: QuickSort (branchless CMOV median-of-three), MergeSort, HeapSort
- **Hybrid**: IntroSort, TimSort, BlockSort
- **Linear-Time**: RadixSort (LSD/MSD), CountingSort, BucketSort, PigeonholeSort, BitonicSort

#### Searching Algorithms
- Linear Search, Binary Search, Interpolation Search

#### Smart Dispatcher
- Automatic $O(N)$ data profiling via `DataTraits` (size, sortedness ratio)
- Selects the optimal algorithm at runtime — no manual tuning required
- Runtime overrides via JSON configuration (`nlohmann/json`)

#### Domain-Specific Numerics ($O(N)$ Fast Paths)
- **Boolean arrays** — branchless counting pass (~23x faster than `numpy.sort`)
- **Float16** — custom bit-flipping with L2-aligned 16-bit Counting Sort (~2.2x faster than `numpy.sort`)
- **Complex64/128** — 64-bit Morton Z-order keys + 4-pass 16-bit Radix Sort for spatial locality (~2.0x faster than `numpy.sort`)

#### Python Bindings
- Zero-copy integration via `nanobind` for NumPy arrays and Python lists
- `algoat.sort()` — returns a sorted copy with smart dispatch
- `algoat.sort_inplace()` — zero-allocation in-place sort
- `algoat.search()` — search with automatic algorithm selection

### 📦 Platform Support

| Platform | Architectures |
| :--- | :--- |
| **Linux** (manylinux_2_28) | x86_64 |
| **macOS** | x86_64, ARM64 (Apple Silicon) |
| **Windows** | x86_64 |
| **Python** | 3.10, 3.11, 3.12, 3.13, 3.14 |

### 🔧 CI & Build
- Automated wheel builds via `cibuildwheel` across all supported platforms
- Automated PyPI publishing on GitHub Release via Trusted Publisher
- GitHub Release Drafter for changelog automation

### 🐛 Bug Fixes (Pre-Release)
- Fix macOS wheel link failure by removing private CPython bigint APIs ([#1](https://github.com/Sambit003/algoat/issues/1))
- Fix ubuntu wheel build failure by using a newer manylinux image ([#2](https://github.com/Sambit003/algoat/issues/2))
- Skip i686 builds — incompatible with NumPy ≥2.5 (requires GCC ≥10.3)

---

**Full Changelog**: https://github.com/Sambit003/algoat/commits/v0.1.0
