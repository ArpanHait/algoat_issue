#include <algoat/core/dispatcher.hpp>
#include <iostream>
#include <span>
#include <vector>

int main() {
    std::vector<int> data = {5, 2, 8, 1, 9};
    algoat::core::Dispatcher<int> dispatcher;
    dispatcher.sort(data);

    if (data[0] == 1 && data[4] == 9) {
        std::cout << "Algoat Conan package works successfully!\n";
        return 0;
    }
    return 1;
}
