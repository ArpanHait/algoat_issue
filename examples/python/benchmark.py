#!/usr/bin/env python3
"""Algoat vs Python Native — Performance Benchmark

Compares algoat's C++ backed sort/search against Python builtins
across varying dataset sizes.
"""

import time
import random
import statistics
import bisect
import gc
import algoat


def bench(fn, *, warmup=3, runs=50):
    """Run fn() `runs` times after warmup with isolated GC, return median time in µs."""
    for _ in range(warmup):
        fn()
    gc.collect()
    gc.disable()
    times = []
    for _ in range(runs):
        t0 = time.perf_counter_ns()
        fn()
        t1 = time.perf_counter_ns()
        times.append((t1 - t0) / 1_000)  # ns → µs
    gc.enable()
    return statistics.median(times)


def bench_sort(sort_fn, data, *, warmup=3, runs=50):
    """Run sort_fn on pre-allocated copies of data with isolated GC, return median time in µs."""
    for _ in range(warmup):
        sort_fn(data.copy())

    copies = [data.copy() for _ in range(runs)]

    gc.collect()
    gc.disable()
    times = []
    for copy in copies:
        t0 = time.perf_counter_ns()
        sort_fn(copy)
        t1 = time.perf_counter_ns()
        times.append((t1 - t0) / 1_000)  # ns → µs
    gc.enable()
    return statistics.median(times)


def generate_data(n, seed=42):
    rng = random.Random(seed)
    return [rng.randint(0, n * 10) for _ in range(n)]


def run_sort_benchmarks(sizes):
    print("=" * 86)
    print("SORTING BENCHMARK — algoat.sort() vs algoat.sort_inplace() vs native")
    print("=" * 86)
    print(f"{'N':>10} │ {'algoat (µs)':>14} │ {'inplace (µs)':>14} │ {'sorted()':>12} │ {'list.sort()':>13} │ {'Ratio':>8}")
    print("─" * 10 + "─┼─" + "─" * 14 + "─┼─" + "─" * 14 + "─┼─" + "─" * 12 + "─┼─" + "─" * 13 + "─┼─" + "─" * 8)

    results = []
    for n in sizes:
        data = generate_data(n)

        t_algoat = bench_sort(algoat.sort, data)
        t_inplace = bench_sort(algoat.sort_inplace, data)
        t_sorted = bench_sort(sorted, data)
        t_listsort = bench_sort(lambda d: d.sort(), data)

        # Compare inplace to list.sort()
        ratio = t_inplace / t_listsort if t_listsort > 0 else float('inf')
        results.append((n, t_algoat, t_inplace, t_sorted, t_listsort, ratio))

        print(f"{n:>10,} │ {t_algoat:>14.2f} │ {t_inplace:>14.2f} │ {t_sorted:>12.2f} │ {t_listsort:>13.2f} │ {ratio:>7.2f}x")

    return results


def run_search_benchmarks(sizes):
    print()
    print("=" * 72)
    print("SEARCHING BENCHMARK — algoat.search() vs bisect vs list.index()")
    print("=" * 72)
    print(f"{'N':>10} │ {'algoat (µs)':>14} │ {'bisect (µs)':>14} │ {'index() (µs)':>14} │ {'Ratio':>8}")
    print("─" * 10 + "─┼─" + "─" * 14 + "─┼─" + "─" * 14 + "─┼─" + "─" * 14 + "─┼─" + "─" * 8)

    results = []
    for n in sizes:
        data = generate_data(n)
        sorted_data = sorted(data)
        # Pick a target we know exists
        target = sorted_data[n // 3]

        # algoat.search on sorted data
        t_algoat = bench(lambda: algoat.search(sorted_data, target))

        # bisect (binary search) on sorted data
        def bisect_search():
            idx = bisect.bisect_left(sorted_data, target)
            return idx if idx < len(sorted_data) and sorted_data[idx] == target else None

        t_bisect = bench(bisect_search)

        # list.index (linear scan)
        t_index = bench(lambda: sorted_data.index(target))

        ratio = t_algoat / t_bisect if t_bisect > 0 else float('inf')
        results.append((n, t_algoat, t_bisect, t_index, ratio))

        print(f"{n:>10,} │ {t_algoat:>14.2f} │ {t_bisect:>14.2f} │ {t_index:>14.2f} │ {ratio:>7.2f}x")

    return results


def main():
    print("╔══════════════════════════════════════════════════════════════════════╗")
    print("║         Algoat vs Python Native — Performance Benchmark            ║")
    print("║         Median of 50 runs per size (3 warmup iterations)           ║")
    print("╚══════════════════════════════════════════════════════════════════════╝")
    print()

    sizes = [100, 1_000, 10_000, 50_000, 100_000]

    sort_results = run_sort_benchmarks(sizes)
    search_results = run_search_benchmarks(sizes)

    print()
    print("=" * 72)
    print("ANALYSIS")
    print("=" * 72)
    print()
    print("Ratio = algoat / native (< 1.0 means algoat is faster)")
    print()
    print("Note: algoat pays a fixed cost for list→vector copy across the")
    print("Python/C++ boundary. Python's sorted()/bisect are implemented in")
    print("highly optimized C (Timsort / bisect module). The overhead of")
    print("nanobind marshalling dominates at small N, but algoat's dispatch")
    print("engine demonstrates competitive throughput at larger scales.")


if __name__ == "__main__":
    main()
