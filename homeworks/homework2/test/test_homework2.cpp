#include "gtest/gtest.h"
#include "ip_pool.h"

using namespace homework2;

TEST(Homework2, DefaultPool) {
    IpPool pool {};
    ASSERT_EQ(pool.size(), 0);
}

TEST(Homework2, ValidPoolFromFile) {
    fs::path path{"ip_filter.tsv"};
    IpPool pool {path};
    ASSERT_EQ(pool.size(), 1000);
}