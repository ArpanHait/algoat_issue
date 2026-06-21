#pragma once

#include <string_view>
#include <span>
#include <cstddef>
#include <vector>
#include <utility>

namespace algoat::sorting {

struct MergeSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "mergesort";
    }

    template<typename T>
    void sort(std::span<T> data) const {
        if (data.size() <= 1) return;
        std::vector<T> buffer(data.size());
        mergesort_impl(data.data(), buffer.data(), 0, data.size() - 1);
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 32;
    }

private:
    template<typename T>
    void mergesort_impl(T* arr, T* temp, std::size_t left, std::size_t right) const {
        if (left < right) {
            std::size_t mid = left + (right - left) / 2;
            mergesort_impl(arr, temp, left, mid);
            mergesort_impl(arr, temp, mid + 1, right);
            merge(arr, temp, left, mid, right);
        }
    }

    template<typename T>
    void merge(T* arr, T* temp, std::size_t left, std::size_t mid, std::size_t right) const {
        std::size_t i = left;
        std::size_t j = mid + 1;
        std::size_t k = left;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) { // <= ensures stability
                temp[k++] = std::move(arr[i++]);
            } else {
                temp[k++] = std::move(arr[j++]);
            }
        }

        while (i <= mid) {
            temp[k++] = std::move(arr[i++]);
        }

        while (j <= right) {
            temp[k++] = std::move(arr[j++]);
        }

        for (std::size_t p = left; p <= right; ++p) {
            arr[p] = std::move(temp[p]);
        }
    }
};

} // namespace algoat::sorting
