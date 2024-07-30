cmake_minimum_required(VERSION 3.5)
project(UserInfoManager)

file(GLOB_RECURSE SRC src/*.cpp)
if (UNIX) 
    find_package(mysql-concpp REQUIRED)
    add_library(${PROJECT_NAME} STATIC ${SRC})

    target_include_directories(${PROJECT_NAME} PUBLIC include)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONCPP_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} mysql::concpp-jdbc)
elseif(WIN32)
    add_library(${PROJECT_NAME} STATIC ${SRC})
    target_include_directories(${PROJECT_NAME} PUBLIC include)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONNECTOR_CPP_DIR}/include)

    target_link_libraries(${PROJECT_NAME} mysqlcppconn)
endif()


