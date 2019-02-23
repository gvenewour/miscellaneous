project(homework7)

include(${CMAKE_SOURCE_DIR}/cmake/findcppfs.cmake)
find_cppfs()

set(EXECUTABLE "bulk")

set(HEADERS "include/common.h"
            "include/logger.h"
            "include/parser.h"
            "include/storage.h")
set(SRC "src/parser.cpp")

set(ADDITIONAL_LIBS ${CPPFS_LIBRARY})

include(${CMAKE_SOURCE_DIR}/cmake/generate_project.cmake)
generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")