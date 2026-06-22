#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

namespace algoat::sorting {

struct CountingSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "countingsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<typename T>
    void sort(std::span<T> arr) const {
        if constexpr (!std::is_integral_v<T>) {
            throw std::invalid_argument("CountingSort requires an integral type");
        } else {
            if (arr.empty()) return;
            
            auto [min_it, max_it] = std::minmax_element(arr.begin(), arr.end());
            T min_val = *min_it;
            T max_val = *max_it;
            
            using U = std::make_unsigned_t<T>;
            U range = static_cast<U>(max_val - min_val) + 1;
            
            std::vector<std::size_t> count(range, 0);
            for (T x : arr) {
                count[static_cast<U>(x - min_val)]++;
            }
            
            for (std::size_t i = 1; i < range; ++i) {
                count[i] += count[i - 1];
            }
            
            std::vector<T> output(arr.size());
            for (std::size_t i = arr.size(); i-- > 0;) {
                output[count[static_cast<U>(arr[i] - min_val)] - 1] = arr[i];
                count[static_cast<U>(arr[i] - min_val)]--;
            }
            
            std::copy(output.begin(), output.end(), arr.begin());
        }
    }
};

} // namespace algoat::sorting
