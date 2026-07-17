cmake_minimum_required(VERSION 3.10)
project(vdmg)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
include_directories(include)
add_executable(
    bin
    src/main.cpp
    src/mmu.cpp
    src/vdmg.cpp
    src/cpu/cpu.cpp
    src/cpu/ops_cb.cpp
    src/cpu/ops.cpp
    src/cpu/step.cpp
)
if (MINGW)
    target_link_libraries(bin PRIVATE "stdc++exp")
endif()