project(homework3)

set(EXECUTABLE "allocator")
#set(TEST_HOMEWORK3 "test_${EXECUTABLE}")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.58 REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include)

file (GLOB HEADERS_HOMEWORK3 "include/common.h"
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
file (GLOB SRC_HOMEWORK3 "src/example_boost_pool.cpp"
                         "src/example_custom_allocator.cpp"
                         "src/example_interprocess_allocators.cpp"
                         "src/example_custom_list.cpp"
     )

set(SRC_REQUIRED ${HEADERS_HOMEWORK3} ${SRC_HOMEWORK3})

add_executable(${EXECUTABLE} "main.cpp" ${SRC_REQUIRED})
target_link_libraries(${EXECUTABLE} ${LIB} Boost::system pthread rt)

#add_executable(${TEST_HOMEWORK3} "test/test_homework3.cpp" ${SRC_REQUIRED})
#target_link_libraries(${TEST_HOMEWORK3} gtest_main)

set_target_properties(${EXECUTABLE} PROPERTIES
                        CXX_STANDARD 14
                        CXX_STANDARD_REQUIRED ON
                        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                     )

install(TARGETS ${EXECUTABLE} DESTINATION ${INSTALL_PATH}/${INSTALL_BIN_DIR})

#add_test(NAME homework3_tests COMMAND ${TEST_HOMEWORK3} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})