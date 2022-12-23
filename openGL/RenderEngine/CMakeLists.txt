cmake_minimum_required(VERSION 3.0.0)
project(Barrel VERSION 0.1.0)
# C++ Version 17
set (CMAKE_CXX_STANDARD 17)
# Testing
include(CTest)
enable_testing()
# Locations for files
file(GLOB SOURCES_CPP "src/barrel/*.cpp")
file(GLOB SOURCES_BARREL_HPP "src/barrel/*.hpp")
file(GLOB SOURCES_HPP "src/*.hpp")

# Create library
add_library(Barrel SHARED ${SOURCES_CPP} ${SOURCES_HPP} ${SOURCES_BARREL_HPP})


# -------- Third parties libraries -------- #
include(FetchContent)
# Logging
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 #release-1.11.0
)
FetchContent_MakeAvailable(spdlog)
target_link_libraries(Barrel spdlog::spdlog)








set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
