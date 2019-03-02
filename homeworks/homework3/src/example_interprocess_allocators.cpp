/** @file
* @brief Function homework3::exampleShmAllocator
*/

#include <boost/functional/hash.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/unordered_map.hpp>

#include <cassert>

#include "common.h"
#include "example_interprocess_allocators.h"


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
        constexpr auto segmentName {"homework3-shm"};

        //could use create_only as we delete the segment from /run/shm at the end
        shm::Segment segment {boost::interprocess::open_or_create, segmentName, allocSize};
        LOG(INFO) << "Created a named segment in shared memory. Segment name: " << segmentName
                                                                                << ", segment size: " << allocSize;

        shm::VoidAllocator allocator{segment.get_segment_manager()};
        LOG(INFO) << "Created allocator in segment " << segmentName;

        //  constexpr uint8_t initialBucketCount = 2;

        try {
            constexpr auto mainMapName {"main"};
            constexpr auto bufferMapName {"buffer"};

            shm::Map *map = {segment.find_or_construct<shm::Map>(mainMapName)(allocator)};
            LOG(INFO) << "Created an empty map in segment " << segmentName << ", map name: " << mainMapName;

            shm::Map *buffer = {segment.find_or_construct<shm::Map>("Copy")(allocator)};
            LOG(INFO) << "Created another empty map in segment " << segmentName << ", map name: " << bufferMapName;

            std::array<Key, maxCount> identifiers {9990, 2077, 2014, 2012, 1984, 1939, 1937, 1917, 1905, 1861};

            for (const auto& id: identifiers) {
                shm::ValSet tmp(allocator);

                for (auto i = 100500; i < 100510; ++i) {
                    tmp.insert(i - id);
                }

                buffer->insert(shm::Pair{id, boost::move(tmp)});

                assert(tmp.empty());
            }

            LOG(INFO) << "Initialized the buffer map. It now has " << buffer->size() << " keys with 10 values for each";

            *map = boost::move(*buffer);
            LOG(INFO) << "Moved buffer map content to the main map. Buffer map is now empty";

            assert(buffer->empty());

            constexpr uint16_t requiredId = 1984;
            auto id = map->find(requiredId);

            auto printVal = [&id]() {   std::ostringstream log;
                                        for (const auto& val: id->second) {
                                            log << val << " ";
                                        }
                                        return log.str();
                                    };

            LOG(INFO) << "Values elements for id " << requiredId << " in main map: " << printVal();

        } catch (const boost::interprocess::bad_alloc& exception) {
            LOG(WARNING) << "Something went wrong with shm allocation!";
        }

        boost::interprocess::shared_memory_object::remove(segmentName);

        LOG(INFO) << "Removed segment  " << segmentName << " from shared memory";
    }
}