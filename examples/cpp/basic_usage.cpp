#include <algoat/algoat.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <span>

int main() {
    std::cout << "--- Algoat Basic Usage Example ---\n\n";

    // 1. Without Config (Auto Dispatch)
    std::cout << "[Auto Dispatch]\n";
    std::vector<int> data = {42, 7, 19, 100, 3, 55, 21};
    
    std::cout << "Original data: ";
    for (int v : data) std::cout << v << " ";
    std::cout << "\n";

    algoat::sort(std::span{data});
    
    std::cout << "Sorted data:   ";
    for (int v : data) std::cout << v << " ";
    std::cout << "\n";

    int target = 19;
    auto res = algoat::search(std::span{data}, target);
    if (res) {
        std::cout << "Found " << target << " at index " << *res << "\n";
    } else {
        std::cout << "Could not find " << target << "\n";
    }

    // 2. With Config Override
    std::cout << "\n[Config Override]\n";
    
    std::ofstream config_file("example_config.json");
    config_file << R"({
        "sorting": {"prefer": "heapsort"},
        "searching": {"prefer": "linearsearch"}
    })";
    config_file.close();

    algoat::load_global_config("example_config.json");

    std::vector<int> data2 = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    algoat::sort(std::span{data2});
    
    std::cout << "Sorted data (heapsort): ";
    for (int v : data2) std::cout << v << " ";
    std::cout << "\n";

    int target2 = 7;
    auto res2 = algoat::search(std::span{data2}, target2);
    if (res2) {
        std::cout << "Found " << target2 << " at index " << *res2 << " (linearsearch)\n";
    }

    return 0;
}
