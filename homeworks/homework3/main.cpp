#include <iostream>
#include <map>

#include "linear_allocator.h"
#include "custom_list.h"

//tgamma = (n-1)!
constexpr int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}

int main(int argc, char *argv[])
{
    using Key = int;
    using Val = int;

    constexpr uint8_t maxCount {10};

    std::map<Key, Val> simpleMap {};
    for (auto i = 0; i < maxCount; ++i) {
        simpleMap[i] = factorial(i);
    }

    std::map<Key, Val, std::less<>, homework3::LinearAllocator<std::pair<const Key, Val>, maxCount> > map {};
    for (auto i = 0; i < maxCount; ++i) {
        map[i] = factorial(i);
    }

    for (const auto& it : map) {
        std::cout << it.first << " " << it.second << "\n";
    }

    homework3::CustomList<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8};
    list.insert(9);

    homework3::CustomList<int, homework3::LinearAllocator<int, maxCount> > customList{0, 1, 2, 3, 4};

    for (auto i = 5; i < maxCount; ++i) {
        customList.insert(i);
    }

    for (const auto& it: customList) {
        std::cout << it << " ";
    }
    std::cout << "\n";


    return 0;
}
