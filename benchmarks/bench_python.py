import timeit
import gc
import numpy as np
import algoat

def bench_op(sort_fn, data, number=10):
    """Run sort_fn on pre-allocated copies of data with isolated GC."""
    copies = [data.copy() for _ in range(number)]
    gc.collect()
    gc.disable()
    total_time = 0.0
    for copy in copies:
        total_time += timeit.timeit(lambda: sort_fn(copy), number=1)
    gc.enable()
    return total_time

def benchmark_sorting():
    sizes = [10_000, 100_000, 1_000_000]

    for size in sizes:
        print(f"\n--- Array Size: {size} ---")

        # 1. Float16 sorting
        arr_f16 = np.random.rand(size).astype(np.float16)
        # require 'A' so it's memory aligned, just in case
        arr_f16_aligned = np.require(arr_f16, requirements=['A'])

        t_np_f16 = bench_op(np.sort, arr_f16_aligned, number=10)
        t_algoat_f16 = bench_op(algoat.sort, arr_f16_aligned, number=10)

        print(f"Float16 np.sort:     {t_np_f16:.4f} s")
        print(f"Float16 algoat.sort: {t_algoat_f16:.4f} s")
        print(f"Speedup:             {t_np_f16 / t_algoat_f16:.2f}x")

        # 2. Complex64 sorting (Morton Z-order)
        # numpy doesn't naturally sort complex like we do (we use Morton), but we can still benchmark speed.
        # np.sort on complex arrays sorts by real part, then imaginary part.
        arr_c64 = (np.random.rand(size) + 1j * np.random.rand(size)).astype(np.complex64)

        t_np_c64 = bench_op(np.sort, arr_c64, number=10)
        t_algoat_c64 = bench_op(algoat.sort, arr_c64, number=10)

        print(f"Complex64 np.sort:     {t_np_c64:.4f} s")
        print(f"Complex64 algoat.sort: {t_algoat_c64:.4f} s")
        print(f"Speedup:               {t_np_c64 / t_algoat_c64:.2f}x")

        # 3. Boolean sorting
        arr_bool = np.random.choice([False, True], size=size)

        t_np_bool = bench_op(np.sort, arr_bool, number=10)
        t_algoat_bool = bench_op(algoat.sort, arr_bool, number=10)

        print(f"Bool np.sort:     {t_np_bool:.4f} s")
        print(f"Bool algoat.sort: {t_algoat_bool:.4f} s")
        print(f"Speedup:          {t_np_bool / t_algoat_bool:.2f}x")

if __name__ == '__main__':
    benchmark_sorting()

