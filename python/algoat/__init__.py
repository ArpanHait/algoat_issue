from . import _algoat_impl
from ._algoat_impl import sort_inplace, search, load_global_config
import numpy as np

def sort(data):
    if isinstance(data, np.ndarray):
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

__all__ = ["sort", "sort_inplace", "search", "load_global_config"]
