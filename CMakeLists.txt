cmake_minimum_required(VERSION 3.10)
project(MutationSimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(sim main.cpp)

target_include_directories(
    sim
    PUBLIC
    ${PROJECT_SOURCE_DIR}/
)