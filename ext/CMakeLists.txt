cmake_minimum_required(VERSION 2.6.2)

#https://github.com/google/googletest/issues/709
if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
  set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

project(googletest-distribution)

enable_testing()

option(BUILD_GTEST "Builds the googletest subproject" ON)

#Note that googlemock target already builds googletest
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

if(BUILD_GMOCK)
  add_subdirectory( googlemock )
elseif(BUILD_GTEST)
  add_subdirectory( googletest )
endif()
