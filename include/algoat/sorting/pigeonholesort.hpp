#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

namespace algoat::sorting {

struct PigeonholeSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "pigeonholesort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<typename T>
    void sort(std::span<T> arr) const {
        if constexpr (!std::is_integral_v<T>) {
            throw std::invalid_argument("PigeonholeSort requires an integral type");
        } else {
            if (arr.empty()) return;

            auto [min_it, max_it] = std::minmax_element(arr.begin(), arr.end());
            T min_val = *min_it;
            
            using U = std::make_unsigned_t<T>;
            U range = static_cast<U>(*max_it - min_val) + 1;
            
            std::vector<std::size_t> holes(range, 0);
            for (T x : arr) {
                holes[static_cast<U>(x - min_val)]++;
            }
            
            std::size_t idx = 0;
            for (U i = 0; i < range; ++i) {
                while (holes[i] > 0) {
                    arr[idx++] = static_cast<T>(i) + min_val;
                    holes[i]--;
                }
            }
        }
    }
};

} // namespace algoat::sorting
