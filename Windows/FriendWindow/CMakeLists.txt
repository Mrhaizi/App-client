cmake_minimum_required(VERSION 3.5)

project(FriendWindow)

# 收集源文件
file(GLOB_RECURSE SRC src/*.cpp)

# 处理UI文件生成头文件
file (GLOB_RECURSE UI_FILES ui/*.ui)
qt5_wrap_ui(UIS_HEADERS ${UI_FILES})

#生存moc文件
file(GLOB_RECURSE MOC_HEADERS include/*.h)
qt5_wrap_cpp(MOC_SRCS ${MOC_HEADERS})


# 添加库
add_library(${PROJECT_NAME} STATIC ${SRC} ${UIS_HEADERS} ${MOC_SRCS})


# 包含头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/Windows/${PROJECT_NAME})

if(WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONNECTOR_CPP_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        Qt5::Widgets
                                        Qt5::Core
                                        Qt5::Gui
                                        PersonManager
                                        ListItemBase
                                        ConnectPool
                                        )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        PersonManager
                                        ListItemBase
                                        ConnectPool
                                        )
endif()
