cmake_minimum_required(VERSION 3.5)
project(App)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 设置生成器平台为x64
if(NOT DEFINED CMAKE_GENERATOR_PLATFORM)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -fexec-charset=utf-8")

if (WIN32)
    message("windows system")
    set(MYSQL_CONNECTOR_CPP_DIR "C:/Program Files/MySQL/mysql-connector-c++-9.0.0-winx64")
    # set(CMAKE_PREFIX_PATH  "C:/Program Files/MySQL/mysql-connector-c++-9.0.0-winx64/lib/cmake")
    find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core Network)
    find_package(mysql-concpp REQUIRED)
    link_directories(${MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14)
elseif(UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    message("linux system")
    set(CMAKE_PREFIX_PATH "/opt/Qt/5.12.12/gcc_64/lib/cmake/Qt5")
    find_package(Qt5 REQUIRED COMPONENTS Widgets Core Network)
    find_package(mysql-concpp REQUIRED)
    include_directories(${Qt5Core_INCLUDE_DIRS})
endif()
add_subdirectory(Common/Global)
add_subdirectory(Common/ListItemBase)
add_subdirectory(function/Communicator)
add_subdirectory(function/PersonalInfoManager)
add_subdirectory(function/UserInfoManager)
add_subdirectory(Windows/RegisterWindow)
add_subdirectory(Windows/FriendWindow)
add_subdirectory(Windows/GroupWindow)
add_subdirectory(Windows/PlayGameWindow)
add_subdirectory(Windows/LoginWindow)
add_subdirectory(Windows/HomeWindow)


file(GLOB_RECURSE QRC_FILES 
    Windows/LoginWindow/qrc/*.qrc
    )
qt5_add_resources(QT_RESOURCES ${QRC_FILES})

add_executable(App src/main.cpp ${QT_RESOURCES} )

if(WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONNECTOR_CPP_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        LoginWindow
                                        HomeWindow
                                        UserInfoManager
                                        Qt5::Widgets
                                        Qt5::Gui
                                        Qt5::Core)
    #合并后的自定义命令
    add_custom_command(TARGET App POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:App>
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:App>/platforms
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "D:/Qt/5.15.0/msvc2019_64/plugins/platforms"
        $<TARGET_FILE_DIR:App>/platforms
    )

elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        HomeWindow
                                        LoginWindow
                                        Qt5::Widgets
                                        Qt5::Core
                                        Qt5::Gui
                                        UserInfoManager
                                        CommunicatorClient)
endif()

