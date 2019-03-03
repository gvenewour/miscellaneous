#include <iostream>

/** @file
* @brief Решение ДЗ-04
*/

#include "base_cases.h"
#include "tuple_cases.h"

int main () {
    std::cout << "char(-1): "        << homework4::print_ip(char(-1)) << "\n";
    std::cout << "short(0): "        << homework4::print_ip(short(0)) << "\n";
    std::cout << "int(2130706433): " << homework4::print_ip(int(2130706433)) << "\n";
    std::cout << "long(8875824491850138409): "    << homework4::print_ip(long(8875824491850138409))  << "\n";
    std::cout << "std::string{\"trololololo\"}: " << homework4::print_ip(std::string{"trololololo"}) << "\n";

    std::cout << "std::vector<char>{-1, -2, -3, -4}: "
              << homework4::print_ip(std::vector<char>{-1, -2, -3, -4}) << "\n";

    std::cout << "std::vector<std::string>{\"1\", \"2\", \"3\", \"4\"}: "
              << homework4::print_ip(std::vector<std::string>{"1", "2", "3", "4"}) << "\n";

    std::cout << "std::list<int>{1, 2, 3, 4}: "
              << homework4::print_ip(std::list<int>{1, 2, 3, 4}) << "\n";

    std::cout << "std::list<std::string>{\"-1\", \"-2\", \"-3\", \"-4\"}: "
              << homework4::print_ip(std::list<std::string>{"-1", "-2", "-3", "-4"}) << "\n";

    auto niceTuple{std::make_tuple(int(1), long(2), char(-3))};
    std::cout << "std::make_tuple(int(1), long(2), char(-3)): " << homework4::print_ip(niceTuple) << "\n";

    auto mixedTuple{std::make_tuple(std::string{"silent"}, std::string{"hill"}, uint64_t(2))};
    std::cout << "std::make_tuple(std::string{\"silent\"}, std::string{\"hill\"}, uint64_t(2)): "
              <<  homework4::print_ip(mixedTuple) << "\n";

    //auto brokenTuple{std::make_tuple("a", "n")};
    //homework4::print_ip(brokenTuple);

    return 0;
}