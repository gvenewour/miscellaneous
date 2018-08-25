#include "gtest/gtest.h"

#include "lib.h"

TEST(Version, AboveZero) {
    ASSERT_GT(version(), 0);
}
