cmake_minimum_required(VERSION 3.14)

# Project setup
project(vdmg)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Fetch SDL2
include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.12
)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2)

# Include and Source configs
include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define target
add_executable(bin ${SOURCES})

# Attach SDL2
target_link_libraries(bin PRIVATE SDL2::SDL2main SDL2::SDL2-static)

# Resolve linker errors for <print>
if (MINGW) 
    target_link_libraries(bin PRIVATE "stdc++exp")
endif()