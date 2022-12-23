cmake_minimum_required(VERSION 3.0.0)
project(Barrel VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

file(GLOB SOURCES_CPP "src/barrel/*.cpp")
file(GLOB SOURCES_BARREL_HPP "src/barrel/*.hpp")
file(GLOB SOURCES_HPP "src/*.hpp")

add_library(Barrel SHARED ${SOURCES_CPP} ${SOURCES_HPP} ${SOURCES_BARREL_HPP})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
