#!/usr/bin/env python3
"""Algoat Basic Usage Example — Python Edition

Demonstrates sorting, searching, and config-based algorithm overrides
using the algoat Python bindings (backed by C++20 via nanobind).
"""

import json
import tempfile
import os
import algoat


def main():
    print("--- Algoat Basic Usage Example (Python) ---\n")

    # 1. Auto Dispatch (no config)
    print("[Auto Dispatch]")
    data = [42, 7, 19, 100, 3, 55, 21]
    print(f"Original data: {data}")

    sorted_data = algoat.sort(data)
    print(f"Sorted data:   {sorted_data}")

    target = 19
    index = algoat.search(sorted_data, target)
    if index is not None:
        print(f"Found {target} at index {index}")
    else:
        print(f"Could not find {target}")

    # 2. Config Override
    print("\n[Config Override]")
    config = {
        "sorting": {"prefer": "heapsort"},
        "searching": {"prefer": "linearsearch"},
    }

    config_path = os.path.join(tempfile.gettempdir(), "algoat_example_config.json")
    with open(config_path, "w") as f:
        json.dump(config, f)

    algoat.load_global_config(config_path)

    data2 = [9, 1, 8, 2, 7, 3, 6, 4, 5]
    sorted_data2 = algoat.sort(data2)
    print(f"Sorted data (heapsort): {sorted_data2}")

    target2 = 7
    index2 = algoat.search(sorted_data2, target2)
    if index2 is not None:
        print(f"Found {target2} at index {index2} (linearsearch)")

    # 3. Float support
    print("\n[Float Support]")
    floats = [3.14, 1.41, 2.72, 0.58]
    sorted_floats = algoat.sort(floats)
    print(f"Sorted floats: {sorted_floats}")

    # Cleanup
    os.remove(config_path)
    print("\nDone!")


if __name__ == "__main__":
    main()
