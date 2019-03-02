#include "gtest/gtest.h"

#include <map>

#include "common.h"
#include "linear_allocator.h"
#include "custom_list.h"

using namespace homework3;

using CustomMap = std::map<Key, Val, std::less<>, homework3::LinearStatefulAllocator<std::pair<const Key, Val>, maxCount> >;

INITIALIZE_EASYLOGGINGPP    //the logs for test targets are manually disabled in CMakeLists by using ELPP_DISABLE_LOGS

TEST(Homework3, CustomAllocator_MapDefault) {
    CustomMap map{};
    fill<CustomMap>(map);

    ASSERT_EQ(map.size(), maxCount);
    for (const auto& el: map) {
        ASSERT_EQ(el.second, factorial(el.first));
    }
}

TEST(Homework3, CustomAllocator_MapCopyCtor) {
    CustomMap src{};
    fill<CustomMap>(src);

    auto dest = src;

    ASSERT_EQ(dest.size(), maxCount);
    ASSERT_EQ(src.size(), dest.size());

    for (const auto& el: dest) {
        ASSERT_EQ(el.second, src[el.first]);
    }

    for (auto &el: src) {
        el.second = 100500;
    }

    for (const auto& el: dest) {
        ASSERT_EQ(el.second, factorial(el.first));
    }
}

TEST(Homework3, CustomAllocator_MapMoveCtor) {
    CustomMap src{};
    fill<CustomMap>(src);

    auto dest = std::move(src);

    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(dest.size(), maxCount);

    for (const auto& el: dest) {
        ASSERT_EQ(el.second, factorial(el.first));
    }
}

TEST(Homework3, CustomAllocator_MapCopyAssignment) {
    CustomMap src;
    fill<CustomMap>(src);

    CustomMap dest;
    for (auto i = 0; i < maxCount/2; ++i) {
        dest[i] = i;
    }

    dest = src;

    ASSERT_EQ(dest.size(), src.size());

    for (const auto& el: dest) {
        ASSERT_EQ(el.second, src[el.first]);
    }

    for (auto& el: dest) {
        el.second = 6666;
    }

    for (const auto& el: src) {
        ASSERT_EQ(el.second, factorial(el.first));
    }
}

TEST(Homework3, CustomAllocator_MapMoveAssignment) {
    CustomMap src;
    fill<CustomMap>(src);

    CustomMap dest;
    for (auto i = 0; i < maxCount/2; ++i) {
        dest[i] = i;
    }

    dest = std::move(src);

    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(dest.size(), maxCount);

    for (const auto& el: dest) {
        ASSERT_EQ(el.second, factorial(el.first));
    }
}

TEST(Homework3, CustomAllocator_CustomListDefault) {
    homework3::CustomList<Val, homework3::LinearStatefulAllocator<Val, maxCount> > customList{0, 1, 2, 3, 100};
    for (auto i = 5; i < maxCount; ++i) {
        customList.insert(i);
    }

    ASSERT_EQ(customList.size(), maxCount);
}
