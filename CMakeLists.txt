cmake_minimum_required(VERSION 3.20)

project(ragdoll LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)

add_executable(ragdoll
    ragdoll.cpp
    glad.c
)

target_include_directories(ragdoll PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ragdoll PRIVATE
    glfw
)
