project(homework2)

include(${CMAKE_SOURCE_DIR}/cmake/findcppfs.cmake)
find_cppfs()

set(EXECUTABLE "ip_filter")

set(HEADERS "include/ip_address.h"
            "include/ip_pool.h"
            "include/constexpr.h")
set(SRC "src/ip_address.cpp"
        "src/ip_pool.cpp")

set(ADDITIONAL_LIBS ${CPPFS_LIBRARY})

include(${CMAKE_SOURCE_DIR}/cmake/generate_project.cmake)
generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")

file(COPY "test/ip_samples/ip_filter.tsv" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})