cmake_minimum_required(VERSION 3.10)
project(weighterm VERSION 0.1)
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
    )

add_executable(weighterm ${SOURCES})
IF (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE docopt)
ELSE()
    target_link_libraries(${PROJECT_NAME} PRIVATE docopt_s)
ENDIF()

target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::sqlite3::sqlite3)
