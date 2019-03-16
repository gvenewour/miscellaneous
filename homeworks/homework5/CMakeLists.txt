project(homework5)

set(EXECUTABLE "controller")
set(HEADERS "include/common.h"
            "include/controller.h"
            "include/geometry.h"
            "include/model.h"
            "include/view.h")
set(SRC     "src/controller.cpp"
            "src/geometry.cpp"
            "src/model.cpp"
            "src/view.cpp")
set(ADDITIONAL_LIBS "")

include(${CMAKE_SOURCE_DIR}/cmake/generate_project.cmake)
generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")