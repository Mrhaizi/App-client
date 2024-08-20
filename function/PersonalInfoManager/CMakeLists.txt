cmake_minimum_required(VERSION 3.5)
project(PersonalInfoManager)

file(GLOB_RECURSE SRC src/*.cpp)
if (UNIX) 
    add_library(${PROJECT_NAME} STATIC ${SRC})

    target_include_directories(${PROJECT_NAME} PUBLIC include)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONCPP_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME}   mysql::concpp-jdbc
                                            CommunicatorClient)

    
elseif(WIN32)
    add_library(${PROJECT_NAME} STATIC ${SRC})
    target_include_directories(${PROJECT_NAME} PUBLIC include)
    target_include_directories(${PROJECT_NAME} PUBLIC ${MYSQL_CONNECTOR_CPP_DIR}/include)
    target_link_libraries(${PROJECT_NAME} mysqlcppconn)
endif()


