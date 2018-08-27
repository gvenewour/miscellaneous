project(homework3)

set(EXECUTABLE "allocator")
#set(TEST_HOMEWORK3 "test_${EXECUTABLE}")

find_package(Boost 1.58 REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include)

file (GLOB HEADERS_HOMEWORK3 "include/memory_resource.h"
                             "include/arena.h"
                             "include/linear_allocator.h"
                             "include/custom_list.h"
                             "include/custom_list.tpp"
                             "include/custom_list_node.h"
                             "include/custom_list_iterator.h")
file (GLOB SRC_HOMEWORK3 "")

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