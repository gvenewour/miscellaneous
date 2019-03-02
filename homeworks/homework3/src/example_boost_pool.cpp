/** @file
* @brief Function homework3::exampleFastPoolAllocator
*/

#include <map>

#include "common.h"
#include "example_boost_pool.h"

namespace homework3 {
    void exampleFastPoolAllocator() {
        using PoolAllocator =   boost::fast_pool_allocator<Val, boost::default_user_allocator_new_delete,
                                boost::details::pool::default_mutex,
                                sizeof(Val),
                                maxCount * sizeof(Val)>;
        using BoostMap = std::map<Key, Val, std::less<>, PoolAllocator>;

        BoostMap map;
        fill<BoostMap>(map);
        LOG(INFO) << "Map initialized wth PoolAllocator: " << toKeyValString<BoostMap>(map) << "\n";

        boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(Val)>::purge_memory();
    }
}