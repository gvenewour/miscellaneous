#include "example_interprocess_allocators.h"

#include <boost/functional/hash.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/unordered_map.hpp>

#include <cassert>
#include "common.h"


namespace homework3 {
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
}