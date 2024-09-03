cmake_minimum_required(VERSION 3.5)
project(PersonManager)

file(GLOB_RECURSE SRC src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC CommunicatorClient)
                                            

