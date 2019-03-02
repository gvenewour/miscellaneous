project(homework3)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.58 REQUIRED COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Threads REQUIRED)  #for linking pthread

set(EXECUTABLE "allocator")

set(HEADERS "include/common.h"
            "include/memory_resource.h"
            "include/arena.h"
            "include/linear_allocator.h"
            "include/custom_list.h"
            "include/custom_list.tpp"
            "include/custom_list_node.h"
            "include/custom_list_iterator.h"
            "include/example_boost_pool.h"
            "include/example_interprocess_allocators.h"
            "include/examples_custom_allocator.h"
            "include/example_custom_list.h"
     )
set(SRC "src/example_boost_pool.cpp"
         "src/examples_custom_allocator.cpp"
         "src/example_interprocess_allocators.cpp"
         "src/example_custom_list.cpp"
    )

find_library(RT_LIBRARY rt)
set(ADDITIONAL_LIBS ${Boost_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${RT_LIBRARY})  #pthread rt

include(${CMAKE_SOURCE_DIR}/cmake/generate_project.cmake)

add_definitions(-DELPP_NO_LOG_TO_FILE)

generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")