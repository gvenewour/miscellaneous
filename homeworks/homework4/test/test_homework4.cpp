#include "gtest/gtest.h"

#include "base_cases.h"
#include "tuple_cases.h"

using namespace homework4;

TEST(Homework4, CheckNumeric) {
    ASSERT_EQ(print_ip(char(-1)), "255");
    ASSERT_EQ(print_ip(short(0)), "0.0");
    ASSERT_EQ(print_ip(int(2130706433)), "127.0.0.1");
    ASSERT_EQ(print_ip(long(8875824491850138409)), "123.45.67.89.101.112.131.41");
}

TEST(Homework4, CheckContainers) {
    ASSERT_EQ(print_ip(std::string{"trololololo"}), "trololololo");
    ASSERT_EQ(print_ip(std::vector<char>{-1, -2, -3, -4}), "255.254.253.252");
    ASSERT_EQ(print_ip(std::vector<std::string>{"1", "2", "3", "4"}), "1.2.3.4");
    ASSERT_EQ(print_ip(std::list<int>{1, 2, 3, 4}), "1.2.3.4");
    ASSERT_EQ(print_ip(std::list<std::string>{"-1", "-2", "-3", "-4"}), "-1.-2.-3.-4");
}

TEST(Homework4, CheckTuples) {
    ASSERT_EQ(print_ip(std::make_tuple(int(1), long(2), char(-3))), "1.2.253");
    ASSERT_EQ(print_ip(std::make_tuple(std::string{"silent"}, std::string{"hill"}, uint64_t(2))), "silent.hill.2");
}