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


int main(int argc, char *argv[])
{
    using StandardMap = std::map<homework3::Key, homework3::Val>;
    StandardMap simpleMap;
    homework3::fill<StandardMap>(simpleMap);

    std::cout << "=== custom allocator examples: ===" << "\n";
    homework3::examplesCustomAllocator();
    std::cout << "=== custom list example: ===" << "\n";
    homework3::exampleCustomList();

    std::cout << "=== boost fast_pool_allocator example: ===" << "\n";
    homework3::exampleFastPoolAllocator();

    std::cout << "=== boost interprocess allocator for nested containers example: ===" << "\n";
    homework3::exampleShmAllocator();

    return 0;
}