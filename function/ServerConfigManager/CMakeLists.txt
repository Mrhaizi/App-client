cmake_minimum_required(VERSION 3.17)
project(ServerConfigManager)

file(GLOB_RECURSE SRC src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)



