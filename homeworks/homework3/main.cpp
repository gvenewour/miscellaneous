/** @file
* @brief Решение ДЗ-03
*/

#include <iostream>
#include <map>

#include "common.h"

#include "examples_custom_allocator.h"
#include "example_custom_list.h"
#include "example_boost_pool.h"
#include "example_interprocess_allocators.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    START_EASYLOGGINGPP(argc, argv);

    using StandardMap = std::map<homework3::Key, homework3::Val>;
    StandardMap simpleMap;
    homework3::fill<StandardMap>(simpleMap);

    LOG(INFO) << "=== Custom allocator examples: ===";
    homework3::examplesCustomAllocator();

    LOG(INFO) << "\n";

    LOG(INFO) << "=== custom list example: ===";
    homework3::exampleCustomList();
    LOG(INFO) << "\n";

    LOG(INFO) << "=== boost fast_pool_allocator example: ===";
    homework3::exampleFastPoolAllocator();
    LOG(INFO) << "\n";

    LOG(INFO) << "=== boost interprocess allocator for nested containers example: ===";
    homework3::exampleShmAllocator();
    LOG(INFO) << "\n";

    return 0;
}