project(homework7)

include(${CMAKE_SOURCE_DIR}/cmake/findcppfs.cmake)
find_cppfs()

set(EXECUTABLE "bulk")
#set(TEST_EXECUTABLE "test_${EXECUTABLE}")

include_directories(include)

file (GLOB HEADERS_HOMEWORK "include/parser.h"
                            "include/storage.h")
file (GLOB SRC_HOMEWORK "src/parser.cpp")

set(SRC_REQUIRED ${HEADERS_HOMEWORK} ${SRC_HOMEWORK} )

add_executable(${EXECUTABLE} "main.cpp" ${SRC_REQUIRED})
target_link_libraries(${EXECUTABLE} ${LIB} ${CPPFS_LIBRARY})

#add_executable(${TEST_EXECUTABLE} "test/test_${PROJECT_NAME}.cpp" ${SRC_REQUIRED})
#target_link_libraries(${TEST_EXECUTABLE} gtest_main)
set_target_properties(${EXECUTABLE} PROPERTIES
                        CXX_STANDARD 14
                        CXX_STANDARD_REQUIRED ON
                        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                     )

install(TARGETS ${EXECUTABLE} DESTINATION ${INSTALL_PATH}/${INSTALL_BIN_DIR})

#add_test(NAME ${PROJECT_NAME}_tests COMMAND ${TEST_EXECUTABLE} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})