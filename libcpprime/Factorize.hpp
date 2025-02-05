/**
 * libcpprime https://github.com/sortA0329/libcpprime
 * 
 * MIT License
 *
 * Copyright (c) 2024 Rac
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/
#ifndef LIBCPPRIME_INCLUDED_FACTORIZE
#define LIBCPPRIME_INCLUDED_FACTORIZE

#include "./IsPrimeNoTable.hpp"
#include "internal/IsPrimeCommon.hpp"

namespace cppr {

class FactorizeResult {
    friend constexpr FactorizeResult Factorize(std::uint64_t n) noexcept;
    std::uint32_t len;
    std::uint64_t factors[64];
    constexpr FactorizeResult() : len(0), factors() {}
public:
    constexpr const std::uint64_t* data() const noexcept { return factors; }
    constexpr const std::uint64_t* begin() const noexcept { return factors; }
    constexpr const std::uint64_t* end() const noexcept { return factors + len; }
    constexpr const std::uint64_t* cbegin() const noexcept { return factors; }
    constexpr const std::uint64_t* cend() const noexcept { return factors + len; }
    constexpr std::uint32_t size() const noexcept { return len; }
    constexpr std::uint64_t operator[](std::uint32_t idx) const noexcept { return factors[idx]; }
};

namespace internal {
    constexpr std::uint64_t FindFactor(std::uint64_t n) noexcept {
        return n;
    }
    constexpr std::uint64_t* FactorizeSub(std::uint64_t n, std::uint64_t* res) noexcept {
        if (n <= 0xffffffff) {
            if (n < 1024 ? internal::IsPrime10(n) : internal::IsPrime32(n)) {
                *(res++) = n;
                return res;
            }
            return res;
        }
        if (n < (std::uint64_t(1) << 62) ? internal::IsPrime64MillerRabin(n) : internal::IsPrime64BailliePSW(n)) {
            *(res++) = n;
            return res;
        }
        std::uint64_t m = FindFactor(n);
        std::uint64_t op = n / m;
        if (op < 529) *(res++) = op;
        else res = FactorizeSub(op, res);
        if (m < 529) {
            *(res++) = m;
            return res;
        } else return FactorizeSub(m, res);
    }
}  // namespace internal

constexpr FactorizeResult Factorize(std::uint64_t n) noexcept {
    FactorizeResult res;
    if (n <= 1) return res;
    std::uint64_t* ptr = res.factors;
    while (n % 2 == 0) {
        n /= 2;
        *(ptr++) = 2;
    }
    while (n % 3 == 0) {
        n /= 3;
        *(ptr++) = 3;
    }
    while (n % 5 == 0) {
        n /= 5;
        *(ptr++) = 5;
    }
    while (n % 7 == 0) {
        n /= 7;
        *(ptr++) = 7;
    }
    while (n % 11 == 0) {
        n /= 11;
        *(ptr++) = 11;
    }
    while (n % 13 == 0) {
        n /= 13;
        *(ptr++) = 13;
    }
    while (n % 17 == 0) {
        n /= 17;
        *(ptr++) = 17;
    }
    while (n % 19 == 0) {
        n /= 19;
        *(ptr++) = 19;
    }
    if (n >= 529) {
        ptr = internal::FactorizeSub(n, ptr);
    } else {
        *ptr = n;
        ptr += n != 1;
    }
    res.len = ptr - res.factors;
    return res;
}

}  // namespace cppr

#endif
