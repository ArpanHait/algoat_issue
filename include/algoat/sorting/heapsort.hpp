#pragma once

#include <string_view>
#include <span>
#include <cstddef>
#include <utility>

namespace algoat::sorting {

struct HeapSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "heapsort";
    }

    template<typename T>
    void sort(std::span<T> data) const {
        const std::size_t n = data.size();
        if (n <= 1) return;

        // Build heap (rearrange array)
        for (std::size_t i = n / 2; i > 0; --i) {
            heapify(data.data(), n, i - 1);
        }

        // One by one extract an element from heap
        for (std::size_t i = n - 1; i > 0; --i) {
            std::swap(data[0], data[i]);
            heapify(data.data(), i, 0);
        }
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0; // Ideal fallback
    }

private:
    template<typename T>
    void heapify(T* arr, std::size_t n, std::size_t i) const {
        std::size_t largest = i;
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;

        if (left < n && arr[largest] < arr[left]) {
            largest = left;
        }

        if (right < n && arr[largest] < arr[right]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

} // namespace algoat::sorting
