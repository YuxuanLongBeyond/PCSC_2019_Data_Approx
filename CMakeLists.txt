cmake_minimum_required(VERSION 3.15)
project(Integration)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tests)
add_subdirectory(core)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(docs ALL
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generate the docs")
endif (DOXYGEN_FOUND)