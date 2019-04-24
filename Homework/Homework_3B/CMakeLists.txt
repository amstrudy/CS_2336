PROJECT (homework_3b C CXX)

cmake_minimum_required (VERSION 3.1)
add_definitions (-std=c++11 -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(homework_3b
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/Encryption.cpp"
    "${PROJECT_SOURCE_DIR}/src/Uppercase.cpp"
    "${PROJECT_SOURCE_DIR}/src/Copy.cpp"
)
