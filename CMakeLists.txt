cmake_minimum_required(VERSION 3.10)
project(weighterm VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(docopt COMPONENTS CXX REQUIRED)
include_directories(${DOCOPT_INCLUDE_DIRS})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

add_executable(weighterm src/weighterm.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
