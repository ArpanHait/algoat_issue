#pragma once

#include <cstdint>
#include <span>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <cstring>

#if __has_include(<stdfloat>)
#include <stdfloat>
#endif

namespace algoat::concepts {

template <typename T>
concept Size16Bit = sizeof(T) == 2;

template <typename T>
concept Int16 = std::integral<T> && Size16Bit<T> && !std::same_as<std::remove_cv_t<T>, bool>;

template <typename T>
concept Float16 = std::floating_point<T> && Size16Bit<T>;

template <typename T>
concept Float16OrInt16 = Int16<T> || Float16<T>;

} // namespace algoat::concepts

namespace algoat::numerics {

// Using a custom transparent comparator for float16 sign-flipping trick
struct Float16Compare {
    using is_transparent = void;

    template <algoat::concepts::Float16OrInt16 T, algoat::concepts::Float16OrInt16 U>
    constexpr bool operator()(const T& a, const U& b) const noexcept {
        auto to_ordered = [](auto x) -> uint16_t {
            uint16_t u;
            std::memcpy(&u, &x, 2);
            return (u & 0x8000) ? ~u : (u | 0x8000);
        };
        return to_ordered(a) < to_ordered(b);
    }
};

template <algoat::concepts::Float16OrInt16 T>
void sort_float16(std::span<T> data) {
    if (data.size() < 256) {
        std::sort(data.begin(), data.end(), Float16Compare{});
        return;
    }
    
    if (data.size() < 65536) {
        // 2-pass 8-bit Radix Sort for smaller arrays (less memset overhead)
        std::vector<T> buffer(data.size());
        std::span<T> src = data;
        std::span<T> dst = buffer;
        
        for (int shift = 0; shift < 16; shift += 8) {
            std::size_t count[256] = {0};
            
            for (T val : src) {
                uint16_t u;
                std::memcpy(&u, &val, 2);
                uint16_t ordered = (u & 0x8000) ? ~u : (u | 0x8000);
                count[(ordered >> shift) & 0xFF]++;
            }
            
            std::size_t total = 0;
            for (int i = 0; i < 256; ++i) {
                std::size_t oldCount = count[i];
                count[i] = total;
                total += oldCount;
            }
            
            for (T val : src) {
                uint16_t u;
                std::memcpy(&u, &val, 2);
                uint16_t ordered = (u & 0x8000) ? ~u : (u | 0x8000);
                std::size_t bucket = (ordered >> shift) & 0xFF;
                dst[count[bucket]++] = val;
            }
            
            std::swap(src, dst);
        }
    } else {
        // Single-pass 16-bit counting sort (65536 buckets)
        std::size_t count[65536] = {0};
        
        for (T val : data) {
            uint16_t u;
            std::memcpy(&u, &val, 2);
            uint16_t ordered = (u & 0x8000) ? ~u : (u | 0x8000);
            count[ordered]++;
        }
        
        std::size_t total = 0;
        for (int i = 0; i < 65536; ++i) {
            std::size_t oldCount = count[i];
            count[i] = total;
            total += oldCount;
        }
        
        std::vector<T> buffer(data.size());
        for (T val : data) {
            uint16_t u;
            std::memcpy(&u, &val, 2);
            uint16_t ordered = (u & 0x8000) ? ~u : (u | 0x8000);
            buffer[count[ordered]++] = val;
        }
        
        std::copy(buffer.begin(), buffer.end(), data.begin());
    }
}

} // namespace algoat::numerics
