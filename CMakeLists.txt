cmake_minimum_required(VERSION 3.9)

set(VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})

if(NOT DEFINED VERSION_PATCH)
 set(VERSION_PATCH 1)
endif(NOT DEFINED VERSION_PATCH)

project(homeworks VERSION 0.0.${VERSION_PATCH})

set(LIB ${PROJECT_NAME})

add_subdirectory(external/gtest)

include_directories("${CMAKE_SOURCE_DIR}/lib/include"
                    ${CMAKE_BINARY_DIR}     #version.h
                    ${gtest_SOURCE_DIR}
                    ${gtest_SOURCE_DIR}/include)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/results)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/results)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/results)

if (UNIX)
    SET(INSTALL_PATH          "${CMAKE_INSTALL_PREFIX}" CACHE PATH "Installation prefix")
    set(INSTALL_LIB_DIR       lib                       CACHE PATH "Installation directory for libraries")
    set(INSTALL_BIN_DIR       bin                       CACHE PATH "Installation directory for executables")

    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "alla@host.somedomain")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Otus C++ course homeworks")

    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
    elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
    endif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    set(CUSTOM_PACKAGE_SUFFIX "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

    set(CPACK_DEBIAN_FILE_NAME "${CPACK_PACKAGE_NAME}_${CUSTOM_PACKAGE_SUFFIX}.deb")

endif(UNIX)

enable_testing()
add_subdirectory(lib)
add_subdirectory(homeworks)

include(CPack)
