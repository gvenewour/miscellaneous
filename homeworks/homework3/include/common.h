#pragma once

#include <cstdint>
#include <iostream>

using Key = int;
using Val = int;
constexpr uint8_t maxCount {10};

//tgamma = (n-1)!
constexpr int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}

template <typename T>
void fill(T& map) {
    for (auto i = 0; i < maxCount; ++i) {
        map[i] = factorial(i);
    }
}

template <typename T>
void print(T& map) {
    for (const auto& it : map) {
        std::cout << "[" << it.first << " " << it.second << "] ";
    }
    std::cout << "\n";
}