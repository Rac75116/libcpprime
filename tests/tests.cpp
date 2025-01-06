#include <libcpprime/IsPrime.hpp>
#include <libcpprime/IsPrimeNoTable.hpp>
#include <fstream>
#include <iostream>
#include "tests/constexpr_tests.cpp"
int main() {
    {
        std::ifstream ifs("./tests/Primes.txt");
        if (!ifs) return 1;
        std::string line;
        while (std::getline(ifs, line)) {
            std::uint64_t x = std::stoull(line);
            if (!cppr::IsPrime(x) || !cppr::IsPrimeNoTable(x)) return 1;
        }
    }
    {
        std::ifstream ifs("./tests/Composites.txt");
        if (!ifs) return 1;
        std::string line;
        while (std::getline(ifs, line)) {
            std::uint64_t x = std::stoull(line);
            if (cppr::IsPrime(x) || cppr::IsPrimeNoTable(x)) return 1;
        }
    }
}
