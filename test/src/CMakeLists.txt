aux_source_directory(. SRC_LIST)

# find *.h
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/public/include)

# link *.b
link_directories(${PROJECT_SOURCE_DIR}/public/lib)

# 使用变量设置编译标志
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
add_executable(work ${SRC_LIST})
target_link_libraries(work pthread utils)