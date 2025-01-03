#include <libcpprime/IsPrime.hpp>
#include <libcpprime/IsPrimeNoTable.hpp>
#include <random>
#include <iostream>
int main() {
    int a = 0, b = 0;
    std::mt19937_64 engine;
    for (int i = 0; i != 1000000; ++i) {
        a += cppr::IsPrime(engine());
        b += cppr::IsPrimeNoTable(engine());
    }
    std::cout << a << ' ' << b << std::endl;
}
