macro(generate_project NAME EXECUTABLE HEADERS SRC ADDITIONAL_LIBS)
    message(STATUS "=== Generating project ${NAME} with executable ${EXECUTABLE} ===")

    if (NOT(${ARGC} EQUAL 5))
        #   All list args should be bracketed as pointed out here: https://gitlab.kitware.com/cmake/cmake/issues/17113
        #   generate_project(${PROJECT_NAME} ${EXECUTABLE} "${HEADERS}" "${SRC}" "${ADDITIONAL_LIBS}")
        message(FATAL_ERROR "error in generate_project macro call: wrong number of args or no brackets around lists")
    endif()


    include_directories(include)

    set(TEST_EXECUTABLE "test_${EXECUTABLE}")

    add_executable(${EXECUTABLE} "main.cpp"  ${HEADERS} ${SRC})
    target_link_libraries(${EXECUTABLE} ${LIB} ${ADDITIONAL_LIBS})

    add_executable(${TEST_EXECUTABLE} "test/test_${NAME}.cpp" ${HEADERS} ${SRC})
    target_link_libraries(${TEST_EXECUTABLE} gtest_main ${ADDITIONAL_LIBS})

    set_target_properties(${EXECUTABLE} ${TEST_EXECUTABLE} PROPERTIES
                            CXX_STANDARD 14
                            CXX_STANDARD_REQUIRED ON
                            COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                          )

    install(TARGETS ${EXECUTABLE} DESTINATION ${INSTALL_PATH}/${INSTALL_BIN_DIR})

    add_test(NAME ${NAME}_tests COMMAND ${TEST_EXECUTABLE} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endmacro()