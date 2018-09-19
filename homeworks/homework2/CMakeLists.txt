project(homework2)

include(${CMAKE_SOURCE_DIR}/cmake/findcppfs.cmake)
find_cppfs()

set(EXECUTABLE "ip_filter")
set(TEST_HOMEWORK2 "test_${EXECUTABLE}")

include_directories(include)

file (GLOB HEADERS_HOMEWORK2 "include/ip_address.h"
                             "include/ip_pool.h"
                             "include/constexpr.h")

file (GLOB SRC_HOMEWORK2 "src/ip_address.cpp"
                         "src/ip_pool.cpp")

add_executable(${EXECUTABLE} "main.cpp"  ${HEADERS_HOMEWORK2} ${SRC_HOMEWORK2})
target_link_libraries(${EXECUTABLE} ${LIB} ${CPPFS_LIBRARY})

add_executable(${TEST_HOMEWORK2} "test/test_homework2.cpp" ${HEADERS_HOMEWORK2} ${SRC_HOMEWORK2})
target_link_libraries(${TEST_HOMEWORK2} gtest_main ${CPPFS_LIBRARY})

set_target_properties(${EXECUTABLE} ${TEST_HOMEWORK2} PROPERTIES
                        CXX_STANDARD 14
                        CXX_STANDARD_REQUIRED ON
                        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                     )

install(TARGETS ${EXECUTABLE} DESTINATION ${INSTALL_PATH}/${INSTALL_BIN_DIR})

add_test(NAME homework2_tests COMMAND ${TEST_HOMEWORK2} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY "test/ip_samples/ip_filter.tsv" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})