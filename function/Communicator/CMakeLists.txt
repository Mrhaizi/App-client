cmake_minimum_required(VERSION 3.5)

project(CommunicatorClient)

# 收集源文件
file(GLOB_RECURSE SRC src/*.cpp)



#生存moc文件
file(GLOB_RECURSE MOC_HEADERS include/*.h)
qt6_wrap_cpp(MOC_SRCS ${MOC_HEADERS})

# 添加库
add_library(${PROJECT_NAME} STATIC ${SRC} ${MOC_SRCS})

# 包含头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC include)
if(WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONNECTOR_CPP_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        Qt6::Widgets
                                        Qt6::Core
                                        Qt6::Gui)
elseif(UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        Qt6::Network
                                        MessagePackage)

endif()
