cmake_minimum_required(VERSION 3.1.3)

project(pokertools-cpp VERSION 0.1)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-unused-parameter")

aux_source_directory(src LIB_SOURCES)
file(GLOB LIB_HEADERS include/pokertools-cpp/*.hpp)
include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/test)

add_library(${PROJECT_NAME}-shared SHARED ${LIB_SOURCES} ${LIB_HEADERS})
set_target_properties(${PROJECT_NAME}-shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(${PROJECT_NAME}-static ${LIB_SOURCES} ${LIB_HEADERS})
set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

FUNCTION(add_test_pt TARGET)
    add_executable(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} pthread)
    add_test(${TARGET} ${TARGET})
ENDFUNCTION()

add_test_pt(test-performance ${LIB_SOURCES} ${LIB_HEADERS} test/performance.cpp)
add_test_pt(test-correctness ${LIB_SOURCES} ${LIB_HEADERS} test/correctness.cpp)
add_test_pt(test-sample-usage ${LIB_SOURCES} ${LIB_HEADERS} test/sample-usage.cpp)
