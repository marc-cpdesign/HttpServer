cmake_minimum_required(VERSION 3.14)
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(httpServerTest
    main.cpp
    requestHandler.cpp
    requestHandler.h
)

target_link_libraries(httpServerTest
    httpServer::httpServer
)

add_custom_command(
    TARGET httpServerTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:httpServerTest>
    )
