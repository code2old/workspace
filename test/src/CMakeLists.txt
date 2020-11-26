# 添加源文件
aux_source_directory(. SRC_LIST)
# 添加头文件
include_directories(${PROJECT_SOURCE_DIR}/public/include) 
# 查找库文件
find_library(UTILS_LIB utils HINTS ${PROJECT_SOURCE_DIR}/public/bin)
# 生成可执行文件
add_executable (main ${SRC_LIST})
# 连接库文件
target_link_libraries (main ${UTILS_LIB})
# 设置路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
