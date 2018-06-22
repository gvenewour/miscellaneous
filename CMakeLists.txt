cmake_minimum_required(VERSION 3.9)

project(helloworld VERSION 0.0.1)


set(MAIN_TARGET "${PROJECT_NAME}-cli")

add_executable(${MAIN_TARGET} "main.cpp")

set_target_properties(${MAIN_TARGET} PROPERTIES
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                     )

if (UNIX)
    install(TARGETS ${MAIN_TARGET} RUNTIME DESTINATION bin)

    set(CPACK_PACKAGE_NAME ${MAIN_TARGET})

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


