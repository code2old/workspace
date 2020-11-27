cmake_minimum_required(VERSION 2.8)

project(utils)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/public)
set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(bin)
add_subdirectory(src)
