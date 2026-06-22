#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

namespace algoat::sorting {

struct RadixSortLSD {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "radixsortlsd";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<typename T>
    void sort(std::span<T> arr) const {
        if constexpr (!std::is_integral_v<T>) {
            throw std::invalid_argument("RadixSortLSD requires an integral type");
        } else {
            if (arr.empty()) return;

            using U = std::make_unsigned_t<T>;
            const int passes = sizeof(T);
            std::vector<T> buffer(arr.size());
            std::span<T> src = arr;
            std::span<T> dst = buffer;

            for (int shift = 0; shift < passes * 8; shift += 8) {
                std::size_t count[256] = {0};

                for (T val : src) {
                    U u_val = static_cast<U>(val);
                    if constexpr (std::is_signed_v<T>) {
                        u_val ^= (U(1) << (sizeof(T) * 8 - 1));
                    }
                    count[(u_val >> shift) & 0xFF]++;
                }

                std::size_t total = 0;
                for (int i = 0; i < 256; ++i) {
                    std::size_t oldCount = count[i];
                    count[i] = total;
                    total += oldCount;
                }

                for (T val : src) {
                    U u_val = static_cast<U>(val);
                    if constexpr (std::is_signed_v<T>) {
                        u_val ^= (U(1) << (sizeof(T) * 8 - 1));
                    }
                    std::size_t bucket = (u_val >> shift) & 0xFF;
                    dst[count[bucket]++] = val;
                }

                std::swap(src, dst);
            }

            if (passes % 2 != 0) {
                std::copy(buffer.begin(), buffer.end(), arr.begin());
            }
        }
    }
};

struct RadixSortMSD {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "radixsortmsd";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<typename T>
    static void msd_impl(std::span<T> arr, std::span<T> buffer, int shift) {
        if (arr.size() <= 1) return;

        using U = std::make_unsigned_t<T>;
        std::size_t count[256] = {0};

        for (T val : arr) {
            U u_val = static_cast<U>(val);
            if constexpr (std::is_signed_v<T>) {
                u_val ^= (U(1) << (sizeof(T) * 8 - 1));
            }
            count[(u_val >> shift) & 0xFF]++;
        }

        std::size_t boundaries[256];
        std::size_t total = 0;
        for (int i = 0; i < 256; ++i) {
            boundaries[i] = total;
            total += count[i];
        }

        std::size_t offsets[256];
        std::copy(std::begin(boundaries), std::end(boundaries), std::begin(offsets));
        
        for (T val : arr) {
            U u_val = static_cast<U>(val);
            if constexpr (std::is_signed_v<T>) {
                u_val ^= (U(1) << (sizeof(T) * 8 - 1));
            }
            std::size_t bucket = (u_val >> shift) & 0xFF;
            buffer[offsets[bucket]++] = val;
        }

        std::copy(buffer.begin(), buffer.begin() + arr.size(), arr.begin());

        if (shift > 0) {
            for (int i = 0; i < 256; ++i) {
                std::size_t bin_size = count[i];
                if (bin_size > 1) {
                    msd_impl<T>(
                        arr.subspan(boundaries[i], bin_size),
                        buffer.subspan(boundaries[i], bin_size),
                        shift - 8
                    );
                }
            }
        }
    }

    template<typename T>
    void sort(std::span<T> arr) const {
        if constexpr (!std::is_integral_v<T>) {
            throw std::invalid_argument("RadixSortMSD requires an integral type");
        } else {
            if (arr.size() <= 1) return;
            std::vector<T> buffer(arr.size());
            msd_impl<T>(arr, buffer, (sizeof(T) - 1) * 8);
        }
    }
};

} // namespace algoat::sorting
