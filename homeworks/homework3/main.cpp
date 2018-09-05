#include <iostream>
#include <map>

#include <algorithm>
#include <cassert>
#include <vector>

#include <boost/pool/pool_alloc.hpp>

#include <boost/functional/hash.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/unordered_map.hpp>

#include "linear_allocator.h"
#include "custom_list.h"

//tgamma = (n-1)!
constexpr int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}

using Key = int;
using Val = int;
constexpr uint8_t maxCount {10};

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

void exampleCustomAllocator();
void exampleDefault();
void exampleCopyCtor();
void exampleMoveCtor();
void exampleSwap();
void exampleCopyAssignment();
void exampleMoveAssignment();
void exampleCustomList();
void exampleFastPoolAllocator();
void exampleShmAllocator();

int main(int argc, char *argv[])
{
    using StandardMap = std::map<Key, Val>;
    StandardMap simpleMap;
    fill<StandardMap>(simpleMap);

    std::cout << "=== custom allocator examples: ===" << "\n";
    exampleCustomAllocator();
    std::cout << "=== custom list example: ===" << "\n";
    exampleCustomList();

    std::cout << "=== boost fast_pool_allocator example: ===" << "\n";
    exampleFastPoolAllocator();

    std::cout << "=== boost interprocess allocator for nested containers example: ===" << "\n";
    exampleShmAllocator();

    return 0;
}

using CustomMap = std::map<Key, Val, std::less<>, homework3::LinearStatefulAllocator<std::pair<const Key, Val>, maxCount> >;

void exampleCustomAllocator()
{
    exampleDefault();
    exampleCopyCtor();
    exampleMoveCtor();
    exampleSwap();
    exampleCopyAssignment();
    exampleMoveAssignment();
}

void exampleDefault()
{
    std::cout << "==== Default allocator example ====" << "\n";

    CustomMap map{};
    fill<CustomMap>(map);
    std::cout << "--- map: " ; print<CustomMap>(map);
}

void exampleCopyCtor()
{
    std::cout << "==== Container copy constructor example ====" << "\n";

    std::cout << "--- constructing src --- " << "\n";
    CustomMap src{};
    fill<CustomMap>(src);
    std::cout << "--- src: " ; print<CustomMap>(src);

    std::cout << "--- copy constructing dest --- " << "\n";
    auto dest = src;
    std::cout << "--- changed a single element in src --- " << "\n";

    src[0] = 100500;

    std::cout << "--- src: " ; print<CustomMap>(src);
    std::cout << "--- dest (copy): " ; print<CustomMap>(dest);
}

void exampleMoveCtor()
{
    std::cout << "==== Container move constructor example ====" << "\n";
    std::cout << "--- constructing src --- " << "\n";
    CustomMap src{};
    fill<CustomMap>(src);

    std::cout << "--- move constructing dest --- " << "\n";
    auto dest = std::move(src);

    std::cout << "--- src after move: "; print<CustomMap>(src);
    std::cout << "--- dest after move: " ; print<CustomMap>(dest);

    //works only with gcc>=5.5 - https://gcc.gnu.org/viewcvs/gcc?view=revision&revision=238647
    //std::cout << "adding elements to src after move" << "\n";
    //fill<CustomMap>(src);
    //std::cout << "src is valid: "; print<CustomMap>(src);
}

void exampleSwap() {
    std::cout << "==== Container swap example ====" << "\n";

    std::cout << "--- constructing src1 --- " << "\n";
    CustomMap src1;
    fill<CustomMap>(src1);
    src1[0] = 12345;

    std::cout << "--- constructing src2 --- " << "\n";

    CustomMap src2;
    fill<CustomMap>(src2);

    std::cout << "--- src1 before swap: " ; print<CustomMap>(src1);
    std::cout << "--- src2 before swap : " ; print<CustomMap>(src2);

    std::swap(src1, src2);

    std::cout << "--- src1 after swap: " ; print<CustomMap>(src1);
    std::cout << "--- src2 after swap: " ; print<CustomMap>(src2);
}

void exampleCopyAssignment()
{
    std::cout << "==== Container copy assignment example  ====" << "\n";

    std::cout << "--- constructing src --- " << "\n";
    CustomMap src;
    fill<CustomMap>(src); src[0] = 6666;

    std::cout << "--- constructing dest --- " << "\n";

    CustomMap dest;
    fill<CustomMap>(dest); dest[0] = 7777;

    std::cout << "--- src before copy assignment: "; print<CustomMap>(src);
    std::cout << "--- dest before copy assignment: "; print<CustomMap>(dest);

    dest = src;

    std::cout << "--- src after copy assignment: "; print<CustomMap>(src);
    std::cout << "--- dest after copy assignment: "; print<CustomMap>(dest);
}

void exampleMoveAssignment() {
    std::cout << "==== Container move assignment example  ====" << "\n";

    std::cout << "--- constructing src --- " << "\n";
    CustomMap src;
    fill<CustomMap>(src); src[0] = 6666;

    std::cout << "--- constructing dest --- " << "\n";
    CustomMap dest;
    dest[0] = 4321; //and log will contain only 8 additional allocations for dest
    // fill<CustomMap>(dest); src[1] = 7777; //can be uncommented

    std::cout << "--- src before move assignment: "; print<CustomMap>(src);
    std::cout << "--- dest before move assignment: "; print<CustomMap>(dest);

    dest = std::move(src);

    std::cout << "--- src after move assignment: "; print<CustomMap>(src);
    std::cout << "--- dest after move assignment: "; print<CustomMap>(dest);

    //src[11] = 1234;
    // src[12] = 3456; //will throw, need to uncomment _arena->deallocate in the allocator

}

void exampleCustomList() {
    homework3::CustomList<Val> list{0, 1, 2, 3, 4, 5, 6, 7, 8};
    list.insert(9);

    homework3::CustomList<Val, homework3::LinearStatefulAllocator<Val, maxCount> > customList{0, 1, 2, 3, 100};
    for (auto i = 5; i < maxCount; ++i) {
        customList.insert(i);
    }

    std::replace(customList.begin(), customList.end(), 100, 4);    //works!

    for (const auto& it: customList) {
        std::cout << it << " ";
    }
    std::cout << "\n";
}

void exampleFastPoolAllocator() {
    using PoolAllocator = boost::fast_pool_allocator<Val, boost::default_user_allocator_new_delete,
            boost::details::pool::default_mutex,
            sizeof(Val),
            maxCount * sizeof(Val)>;
    using BoostMap = std::map<Key, Val, std::less<>, PoolAllocator>;

    BoostMap map;
    fill<BoostMap>(map);
    print<BoostMap>(map);

    boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(Val)>::purge_memory();
}

namespace shm {
    using Segment         = boost::interprocess::managed_shared_memory;
    using SegmentManager  = Segment::segment_manager;
    using VoidAllocator   = boost::interprocess::allocator<void, SegmentManager>;
    using ValAllocator    = boost::interprocess::allocator<Val, SegmentManager>;
    using ValSet          = boost::interprocess::set<Val, std::less<>, ValAllocator>;
    using Pair            = std::pair<const Key, ValSet>;
    using PairAllocator   = boost::interprocess::allocator<Pair, SegmentManager>;

    using Map = boost::unordered_map<Key, shm::ValSet, boost::hash<Key>, std::equal_to<>, shm::PairAllocator>;
}

void exampleShmAllocator()
{   //id -> Set{unique elements}

    constexpr std::size_t allocSize {sizeof(Val) * 10000};  //random cap, sufficient for this example
    const char segmentName[] = "homework3-shm";

    //could use create_only as we delete the segment from /run/shm at the end
    shm::Segment segment {boost::interprocess::open_or_create, segmentName, allocSize};
    shm::VoidAllocator allocator{segment.get_segment_manager()};

//  constexpr uint8_t initialBucketCount = 2;

    try {
        shm::Map *map = {segment.find_or_construct<shm::Map>("Main")(allocator)};
        shm::Map *buffer = {segment.find_or_construct<shm::Map>("Copy")(allocator)};

        std::array<Key, maxCount> identifiers {9990, 2077, 2014, 2012, 1984, 1939, 1937, 1917, 1905, 1861};

        for (const auto& id: identifiers) {
            shm::ValSet tmp(allocator);

            for (auto i = 100500; i < 100510; ++i) {
                tmp.insert(i - id);
            }

            buffer->insert(shm::Pair{id, boost::move(tmp)});
            assert(tmp.empty());
        }

        *map = boost::move(*buffer);
        assert(buffer->empty());

        constexpr uint16_t requiredId = 1984;
        auto id = map->find(requiredId);
        std::cout << "Saved elements for id " << requiredId << ": ";
        for (const auto& val: id->second) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    } catch (const boost::interprocess::bad_alloc& exception) {
        std::cout << "Something went wrong with shm allocation!" << "\n";
    }

    boost::interprocess::shared_memory_object::remove(segmentName);
}