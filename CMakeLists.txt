cmake_minimum_required(VERSION 3.9)

set(VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})

if(NOT DEFINED VERSION_PATCH)
 set(VERSION_PATCH 1)
endif(NOT DEFINED VERSION_PATCH)

project(helloworld VERSION 0.0.${VERSION_PATCH})

configure_file("version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version.h")

set(LIB "${PROJECT_NAME}")
set(EXECUTABLE "ip_filter")
set(EXECUTABLE_PACKAGE_NAME "${PROJECT_NAME}-cli")
set(TEST_MAIN "test_main-cli")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/"
                    "${CMAKE_CURRENT_BINARY_DIR}")

file (GLOB HEADERS  "${CMAKE_CURRENT_SOURCE_DIR}/include/homework2/ip_address.h"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/homework2/ip_pool.h"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/homework2/constexpr.h")

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/timus.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/homework2/ip_address.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/homework2/ip_pool.cpp")

file(GLOB LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/lib.h")
file(GLOB LIB_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp")

add_library(${LIB} "version.h" ${LIB_HEADERS} ${LIB_SRC_FILES})
add_executable(${EXECUTABLE} "main.cpp"  ${HEADERS} ${SRC})
target_link_libraries(${EXECUTABLE} ${LIB})


#Google test example section
enable_testing()

add_subdirectory(ext)
include_directories("${gtest_SOURCE_DIR}/include" ${gtest_SOURCE_DIR})

add_executable(${TEST_MAIN} "test/test_main.cpp")
target_link_libraries(${TEST_MAIN} ${LIB} gtest_main)

set_target_properties(${EXECUTABLE} ${TEST_MAIN} PROPERTIES
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                     )

add_test(version_validation ${TEST_MAIN})

if (UNIX)
    install(TARGETS ${EXECUTABLE} RUNTIME DESTINATION bin)

    set(CPACK_PACKAGE_NAME ${EXECUTABLE_PACKAGE_NAME})

    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "alla@host.somedomain")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "There is no description for a helloworld app")

    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
    elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
    endif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    set(CUSTOM_PACKAGE_SUFFIX "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

    #because who cares about name conventions?
    set(CPACK_DEBIAN_FILE_NAME "${CPACK_PACKAGE_NAME}_${CUSTOM_PACKAGE_SUFFIX}.deb")

endif(UNIX)

include(CPack)
