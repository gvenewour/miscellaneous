project(homework5)

include(${CMAKE_SOURCE_DIR}/cmake/findcppfs.cmake)
find_cppfs()

set(EXECUTABLE "controller")
set(HEADERS "include/controller.h"
            "include/geometry.h"
            "include/model.h"
            "include/view.h"
            "include/view_cli.h")
set(SRC     "src/controller.cpp"
            "src/geometry.cpp"
            "src/model.cpp"
            "src/view_cli.cpp")
set(ADDITIONAL_LIBS ${CPPFS_LIBRARY})

include(${CMAKE_SOURCE_DIR}/cmake/generate_project.cmake)
generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")