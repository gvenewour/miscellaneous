project(homework3)

set(EXECUTABLE "print_ip")
#set(TEST_EXECUTABLE "test_${EXECUTABLE}")

include_directories(include)

file (GLOB HEADERS_HOMEWORK4    "include/common.h"
                                "include/base_cases.h"
                                "include/tuple_cases.h")
file (GLOB SRC_HOMEWORK4 )

set(SRC_REQUIRED ${HEADERS_HOMEWORK4} ${SRC_HOMEWORK4} )

add_executable(${EXECUTABLE} "main.cpp" ${SRC_REQUIRED})
target_link_libraries(${EXECUTABLE} ${LIB})

#add_executable(${TEST_EXECUTABLE} "test/test_homework4.cpp" ${SRC_REQUIRED})
#target_link_libraries(${TEST_EXECUTABLE} gtest_main)

set_target_properties(${EXECUTABLE} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS ${EXECUTABLE} DESTINATION ${INSTALL_PATH}/${INSTALL_BIN_DIR})

#add_test(NAME homework4_tests COMMAND ${TEST_EXECUTABLE} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})