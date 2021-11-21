cmake_minimum_required(VERSION 3.10)
set(This weighterm)
project(${This} VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Using conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(${DOCOPT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

find_package(docopt COMPONENTS CXX REQUIRED)
find_package(SQLite3)

set(SOURCES
        src/weighterm_data_sqlite.cpp
        src/weight_measure.cpp
        src/weighterm.cpp
        src/weighterm_cli.cpp
    )

set(HEADERS
        src/data_exception.h
        src/weight_measure.h
        src/weighterm_data.h
        src/weighterm_data_sqlite.h
        src/weighterm_cli.h
    )

enable_testing()
add_subdirectory(./libs/googletest)

add_executable(${This} ${SOURCES})
add_library(${This}_lib STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${This} ${CONAN_LIBS})
target_link_libraries(${This}_lib ${CONAN_LIBS})

add_subdirectory(test)
