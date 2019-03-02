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

void reconfigureLog() {
    el::Configurations logConf;
    logConf.setToDefault();
    logConf.setGlobally(el::ConfigurationType::Format, "%datetime{%Y-%M-%d %H:%m:%s} %level     %msg");
    el::Loggers::reconfigureLogger("default", logConf);
}

int main(int argc, char *argv[])
{
    START_EASYLOGGINGPP(argc, argv);
    reconfigureLog();

    using StandardMap = std::map<homework3::Key, homework3::Val>;
    StandardMap simpleMap;
    homework3::fill<StandardMap>(simpleMap);

    LOG(INFO) << "-   Custom allocator examples";
    homework3::examplesCustomAllocator();

    LOG(INFO) << "-   Custom list example";
    homework3::exampleCustomList();

    LOG(INFO) << "-   Boost fast_pool_allocator example";
    homework3::exampleFastPoolAllocator();

    LOG(INFO) << "-   Boost interprocess allocator for nested containers example";
    homework3::exampleShmAllocator();

    return 0;
}