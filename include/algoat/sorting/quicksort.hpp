#pragma once

#include <string_view>
#include <span>
#include <cstddef>
#include <utility>

namespace algoat::sorting {

struct QuickSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "quicksort";
    }

    template<typename T>
    void sort(std::span<T> data) const {
        if (data.size() <= 1) return;
        quicksort_impl(data.data(), 0, data.size() - 1);
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 32;
    }

private:
    template<typename T>
    void quicksort_impl(T* arr, std::size_t low, std::size_t high) const {
        if (low < high) {
            std::size_t pi = partition(arr, low, high);
            if (pi > 0) {
                quicksort_impl(arr, low, pi - 1);
            }
            quicksort_impl(arr, pi + 1, high);
        }
    }

    template<typename T>
    std::size_t median_of_three(T* arr, std::size_t low, std::size_t high) const {
        std::size_t mid = low + (high - low) / 2;
        if (arr[mid] < arr[low]) std::swap(arr[low], arr[mid]);
        if (arr[high] < arr[low]) std::swap(arr[low], arr[high]);
        if (arr[mid] < arr[high]) std::swap(arr[mid], arr[high]);
        return high; // pivot is now at high
    }

    template<typename T>
    std::size_t partition(T* arr, std::size_t low, std::size_t high) const {
        median_of_three(arr, low, high);
        const T& pivot = arr[high];
        std::size_t i = low;

        for (std::size_t j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                std::swap(arr[i], arr[j]);
                i++;
            }
        }
        std::swap(arr[i], arr[high]);
        return i;
    }
};

} // namespace algoat::sorting
