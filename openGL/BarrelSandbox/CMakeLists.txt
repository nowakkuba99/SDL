cmake_minimum_required(VERSION 3.0.0)
project(BarrelSandbox VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)
include(FetchContent)
include(CTest)
enable_testing()

# Add library - Barrel
find_library(BARREL_LIB Barrel)
file(GLOB SOURCES "src/*.cpp")

# Find path for Barrel header file
find_path(BARREL_INCLUDE_DIR Barrel.hpp
    /Users/jakubnowak/Documents/c/repo/SDL/openGL/RenderEngine/src/)

# Create Executuable
add_executable(BarrelSandbox ${SOURCES})


# Include Barrel Header files
target_include_directories(BarrelSandbox
    PUBLIC
    ${BARREL_INCLUDE_DIR}
)

# Link Libraries
target_link_libraries(BarrelSandbox PUBLIC "${BARREL_LIB}")


#message(FATAL_ERROR "${BARREL_LIB}" ${BARREL_INCLUDE_DIR})


# -------- Third parties libraries -------- #
include(FetchContent)
# Logging
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 #release-1.11.0
)
#GlFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        7482de6071d21db77a7236155da44c172a7f6c9e #release-3.3.8
)
FetchContent_MakeAvailable(spdlog glfw)
target_link_libraries(BarrelSandbox PUBLIC spdlog::spdlog glfw)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
