cmake_minimum_required(VERSION 3.5)
project(App-client)


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
    find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core Network WebEngineWidgets)
    find_package(mysql-concpp REQUIRED)
    link_directories(${MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14)
elseif(UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    message("linux system")
    # set(CMAKE_PREFIX_PATH "/opt/Qt/5.12.12/gcc_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "/opt/Qt6/6.8.0/gcc_64")
    set(Qt6_DIR "/opt/Qt6/6.8.0/gcc_64/lib/cmake/Qt6")
    find_package(Qt6 REQUIRED COMPONENTS Widgets Core Network WebEngineWidgets WebSockets)
    find_package(mysql-concpp REQUIRED)
    include_directories(${Qt5Core_INCLUDE_DIRS})
endif()


add_subdirectory(Common/Global)
add_subdirectory(Common/Timer)
add_subdirectory(Common/ListItemBase)
add_subdirectory(Common/Message)
add_subdirectory(function/HttpManager)
add_subdirectory(function/ServerConfigManager)
add_subdirectory(function/Communicator)
add_subdirectory(function/ConnectPool)
add_subdirectory(function/PersonManager)
add_subdirectory(function/WebSocketManager)
add_subdirectory(Windows/RegisterWindow)
add_subdirectory(Windows/LoginWindow)
add_subdirectory(Windows/ChatWindow)
add_subdirectory(Windows/PlayGameWindow)
add_subdirectory(Windows/HomeWindow)
add_subdirectory(Windows/AddressBookWindow)
add_subdirectory(Windows/CommunityWindow)
add_subdirectory(Windows/WebApp)



file(GLOB_RECURSE QRC_FILES 
    Windows/LoginWindow/qrc/*.qrc
    )
qt6_add_resources(QT_RESOURCES ${QRC_FILES})

add_executable(${PROJECT_NAME} src/main.cpp ${QT_RESOURCES} )

target_precompile_headers(${PROJECT_NAME} PRIVATE PreHead/include/phc.h) 

if(WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONNECTOR_CPP_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
                                        LoginWindow
                                        HomeWindow
                                        Qt6::Widgets
                                        Qt6::Gui
                                        Qt6::Core
                                        PersonManager)
    #合并后的自定义命令
    add_custom_command(TARGET App POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Widgets>
        $<TARGET_FILE:Qt6::Gui>
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
                                        Qt6::Widgets
                                        Qt6::Core
                                        Qt6::Gui
                                        Qt6::Network
                                        Qt6::WebEngineWidgets
                                        Qt6::WebSockets
                                        PersonManager
                                        mysql::concpp-jdbc
                                        ConnectPool
                                        ServerConfigManager
                                        CommunicatorClient
                                    )
endif()

