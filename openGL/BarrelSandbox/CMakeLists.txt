cmake_minimum_required(VERSION 3.0.0)
project(BarrelSandbox VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

# Add library - Barrel
find_library(BARREL_LIB Barrel)
file(GLOB SOURCES "src/*.cpp")

# Find path for Barrel header file
find_path(BARREL_INCLUDE_DIR application.hpp
    /Users/jakubnowak/Documents/c/repo/SDL/openGL/RenderEngine/src/)

# Create Executuable
add_executable(BarrelSandbox ${SOURCES})


# Include Barrel Header files
target_include_directories(BarrelSandbox
    PRIVATE
    ${BARREL_INCLUDE_DIR}
)

# Link Libraries
target_link_libraries(BarrelSandbox PRIVATE "${BARREL_LIB}")


#message(FATAL_ERROR "${BARREL_LIB}" ${BARREL_INCLUDE_DIR})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
