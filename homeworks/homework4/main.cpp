#include <iostream>

#include "base_cases.h"
#include "tuple_cases.h"

int main () {
    std::cout << "char(-1): ";                     homework4::print_ip(char(-1));
    std::cout << "short(0): ";                     homework4::print_ip(short(0));
    std::cout << "int(2130706433): ";              homework4::print_ip(int(2130706433));
    std::cout << "long(8875824491850138409): ";    homework4::print_ip(long(8875824491850138409));
    std::cout << "std::string{\"trololololo\"}: "; homework4::print_ip(std::string{"trololololo"});

    std::cout << "std::vector<char>{-1, -2, -3, -4}: ";
    homework4::print_ip(std::vector<char>{-1, -2, -3, -4});

    std::cout << "std::vector<std::string>{\"1\", \"2\", \"3\", \"4\"}: ";
    homework4::print_ip(std::vector<std::string>{"1", "2", "3", "4"});

    std::cout << "std::list<int>{1, 2, 3, 4}: "; homework4::print_ip(std::list<int>{1, 2, 3, 4});
    std::cout << "std::list<std::string>{\"-1\", \"-2\", \"-3\", \"-4\"}: ";
    homework4::print_ip(std::list<std::string>{"-1", "-2", "-3", "-4"});


    auto niceTuple{std::make_tuple(int(1), long(2), char(-3))};
    std::cout << "std::make_tuple(int(1), long(2), char(-3)): "; homework4::print_ip(niceTuple);

    auto mixedTuple{std::make_tuple(std::string{"silent"}, std::string{"hill"}, uint64_t(2))};
    std::cout<< "std::make_tuple(std::string{\"silent\"}, std::string{\"hill\"}, uint64_t(2)): ";
    homework4::print_ip(mixedTuple);

    //auto brokenTuple{std::make_tuple("a", "n")};
    //homework4::print_ip(brokenTuple);

    return 0;
}