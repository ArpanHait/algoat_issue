#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <functional>
#include <vector>
#include <stdexcept>

namespace algoat::core {

template<typename AlgoVariant>
class Registry {
public:
    using FactoryFn = std::function<AlgoVariant()>;

    void register_algo(std::string_view name, FactoryFn factory) {
        std::string name_str{name};
        if (factories_.contains(name_str)) {
            throw std::runtime_error("Algorithm already registered: " + name_str);
        }
        factories_[name_str] = std::move(factory);
    }

    AlgoVariant create(std::string_view name) const {
        std::string name_str{name};
        auto it = factories_.find(name_str);
        if (it == factories_.end()) {
            throw std::runtime_error("Algorithm not found in registry: " + name_str);
        }
        return it->second();
    }

    bool has(std::string_view name) const {
        return factories_.contains(std::string{name});
    }

    std::vector<std::string> list_registered() const {
        std::vector<std::string> names;
        names.reserve(factories_.size());
        for (const auto& [name, _] : factories_) {
            names.push_back(name);
        }
        return names;
    }

private:
    std::unordered_map<std::string, FactoryFn> factories_;
};

} // namespace algoat::core
