"""Algoat: High-performance C++20 and Python algorithm library.

Features smart dynamic fallback dispatch based on data profiles,
domain-specific non-comparative sorting for Float16, boolean, and complex arrays,
zero-copy PEP 3118 memory views, and fine-grained GIL release for multi-core parallelism.
"""

from . import _algoat_impl
from ._algoat_impl import load_global_config, Rational
import numpy as np
from typing import Union, List, Any, Optional

def sort(data: Union[np.ndarray, List[Any]]) -> Union[np.ndarray, List[Any]]:
    """Sort an array or list using smart dynamic algorithm dispatch.

    If given a NumPy ndarray, operates in-place with zero-copy C++ execution and GIL release:
    - `np.float16`: Dispatches to O(N) bit-flipping counting/radix sort.
    - `np.bool_`: Dispatches to branchless O(N) counting pass and memset.
    - `np.complex64` / `np.complex128`: Dispatches to 2D Morton Z-order curve spatial radix sort.
    - Other numeric types (int8..int64, uint8..uint64, float32, float64): Dispatches to dynamic C++ Dispatcher.

    If given a standard Python list, returns a newly allocated sorted list without mutating the original.

    Args:
        data: A NumPy 1D array or a Python list of comparable elements.

    Returns:
        The sorted NumPy array (in-place) or a new sorted Python list.
    """
    if isinstance(data, np.ndarray):
        if not data.flags.c_contiguous and not data.flags.f_contiguous:
            raise ValueError("Sorting requires a contiguous array buffer.")
        if data.dtype == np.float16:
            # We need to view the array as uint16_t to pass it to the C++ extension
            view_arr = data.view(np.uint16)
            _algoat_impl.sort_numpy_f16(view_arr)
            return data
        elif data.dtype == np.bool_:
            view_arr = data.view(np.uint8)
            _algoat_impl.sort_numpy_bool(view_arr)
            return data
        elif data.dtype == np.complex64:
            view_arr = data.view(np.complex64)
            _algoat_impl.sort_numpy_c64(view_arr)
            return data
        elif data.dtype == np.complex128:
            view_arr = data.view(np.complex128)
            _algoat_impl.sort_numpy_c128(view_arr)
            return data
        else:
            _algoat_impl.sort_numpy(data)
            return data
    else:
        return _algoat_impl.sort(data)


def sort_inplace(data: Union[np.ndarray, List[Any]]) -> None:
    """Sort a NumPy array or Python list in-place with zero memory allocation.

    If given a NumPy ndarray:
    - Sorts directly in-place across the contiguous memory buffer with zero heap allocations.
    - Releases the Python GIL during compute to enable concurrent multi-core speedup across worker threads.
    - Requires contiguous memory (C-contiguous or F-contiguous). Non-contiguous slices raise a ValueError.

    If given a standard Python list:
    - Mutates the list in-place by rearranging its internal item pointers.

    Args:
        data: A mutable NumPy 1D array or Python list.
    """
    if isinstance(data, np.ndarray):
        if not data.flags.c_contiguous and not data.flags.f_contiguous:
            raise ValueError("In-place sorting requires a contiguous array buffer.")
        if data.dtype == np.float16:
            # We need to view the array as uint16_t to pass it to the C++ extension
            view_arr = data.view(np.uint16)
            _algoat_impl.sort_numpy_f16(view_arr)
        elif data.dtype == np.bool_:
            view_arr = data.view(np.uint8)
            _algoat_impl.sort_numpy_bool(view_arr)
        elif data.dtype == np.complex64:
            view_arr = data.view(np.complex64)
            _algoat_impl.sort_numpy_c64(view_arr)
        elif data.dtype == np.complex128:
            view_arr = data.view(np.complex128)
            _algoat_impl.sort_numpy_c128(view_arr)
        else:
            _algoat_impl.sort_numpy(data)
    elif type(data) is list:
        _algoat_impl.sort_inplace(data)
    else:
        try:
            _algoat_impl.sort_inplace(data)
        except Exception:
            raise TypeError(f"sort_inplace is not supported for type {type(data).__name__}")


_search_impl = _algoat_impl.search
_search_numpy_impl = _algoat_impl.search_numpy
_search_many_impl = _algoat_impl.search_many
_search_many_numpy_impl = _algoat_impl.search_many_numpy


def search(data: Union[np.ndarray, List[Any]], target: Any) -> Optional[int]:
    """Search for a target value within a sorted array or list using branchless bisection.

    If given a NumPy ndarray, performs zero-copy branchless C++ search directly on contiguous memory with GIL release.
    If given a standard Python list, searches using fast branchless traversal.

    Args:
        data: A sorted NumPy 1D array or sorted Python list.
        target: The value to locate.

    Returns:
        Index of the matching element if found, or None.
    """
    if type(data) is list:
        return _search_impl(data, target)
    elif isinstance(data, np.ndarray):
        return _search_numpy_impl(data, target)
    return _search_impl(data, target)


def search_many(
    data: Union[np.ndarray, List[Any]], targets: Union[np.ndarray, List[Any]]
) -> List[Optional[int]]:
    """Batch search for multiple target values with amortized FFI overhead and GIL release.

    Args:
        data: A sorted array or list to search within.
        targets: An array or list of target values to locate.

    Returns:
        A list of matching indices (or None for targets not found).
    """
    if type(data) is list and type(targets) is list:
        return _search_many_impl(data, targets)
    elif isinstance(data, np.ndarray) and isinstance(targets, np.ndarray):
        return _search_many_numpy_impl(data, targets)
    else:
        list_data = data if isinstance(data, list) else list(data)
        list_targets = targets if isinstance(targets, list) else list(targets)
        return _search_many_impl(list_data, list_targets)


__all__ = ["sort", "sort_inplace", "search", "search_many", "load_global_config", "Rational"]
