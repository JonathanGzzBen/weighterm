cmake_minimum_required(VERSION 3.10)
set(This weighterm)
project(${This} VERSION 0.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Using conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
include_directories(${CMAKE_SOURCE_DIR} ./src)

set(SOURCES
        src/weighterm_data_sqlite.cc
        src/weight_measure.cc
        src/weighterm.cc
        src/weighterm_cli.cc
        src/datetime.cc)

set(HEADERS
        src/data_exception.h
        src/weight_measure.h
        src/weighterm_data.h
        src/weighterm_data_sqlite.h
        src/weighterm_cli.h
        src/datetime.h)

enable_testing()
add_subdirectory(./libs/googletest)

add_executable(${This} ${SOURCES})
add_library(${This}_lib STATIC ${SOURCES} ${HEADERS})

conan_target_link_libraries(${This})
conan_target_link_libraries(${This}_lib)

add_subdirectory(test)
