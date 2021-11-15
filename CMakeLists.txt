cmake_minimum_required(VERSION 3.10)
set(This weighterm)
project(${This} VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Using vcpkg
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(docopt CONFIG REQUIRED)

include_directories(${DOCOPT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

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

IF (WIN32)
    target_link_libraries(${This} PRIVATE docopt)
    target_link_libraries(${This}_lib PRIVATE docopt)
ELSE()
    target_link_libraries(${This} PRIVATE docopt_s)
    target_link_libraries(${This}_lib PRIVATE docopt_s)
ENDIF()

target_link_libraries(${This} PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(${This}_lib PRIVATE unofficial::sqlite3::sqlite3)

add_subdirectory(test)
