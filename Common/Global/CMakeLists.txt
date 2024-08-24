cmake_minimum_required(VERSION 3.5)

project(Global)

# 收集源文件
file(GLOB_RECURSE SRC src/*.cpp)

# 添加库
add_library(${PROJECT_NAME} STATIC ${SRC} ${MOC_SRCS})

# 包含头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC include)
