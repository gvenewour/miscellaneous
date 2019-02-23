project(homework4)

set(EXECUTABLE "print_ip")
set(HEADERS  "include/common.h"
             "include/base_cases.h"
             "include/tuple_cases.h")
set(SRC "")
set(ADDITIONAL_LIBS "")

include(${CMAKE_SOURCE_DIR}/cmake/generate_project.cmake)
generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")