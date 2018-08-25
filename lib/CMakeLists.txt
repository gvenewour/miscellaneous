#add_executable(${TEST_MAIN} "test/test_main.cpp")
#target_link_libraries(${TEST_MAIN} gtest_main ${LIB} )
#
set(TEST_MAIN "test_lib")

configure_file("version.h.in" "${CMAKE_BINARY_DIR}/version.h")

include_directories(${CMAKE_BINARY_DIR} #version.h
                    include)

file(GLOB LIB_HEADERS "include/lib.h")
file(GLOB LIB_SRC_FILES "src/lib.cpp")

add_library(${LIB} "version.h" ${LIB_HEADERS} ${LIB_SRC_FILES})

add_executable(${TEST_MAIN} "test/test_main.cpp" ${LIB_HEADERS} ${LIB_HEADERS})
target_link_libraries(${TEST_MAIN} gtest_main ${LIB})

set_target_properties(${TEST_MAIN} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

add_test(NAME version_validation COMMAND ${TEST_MAIN} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
