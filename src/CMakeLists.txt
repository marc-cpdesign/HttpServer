cmake_minimum_required(VERSION 3.14)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_library(httpServer
        httpServer/httpConnection.cpp
        httpServer/httpData.cpp
        httpServer/httpRequest.cpp
        httpServer/httpRequestRouter.cpp
        httpServer/httpResponse.cpp
        httpServer/httpServer.cpp
        httpServer/middleware/CORS.cpp
        httpServer/middleware/auth.cpp
        httpServer/middleware/getArray.cpp
        httpServer/middleware/getObject.cpp
        httpServer/middleware/verifyJson.cpp
        httpServer/util.cpp

        httpServer/const.h
        httpServer/httpConnection.h
        httpServer/httpCookie.h
        httpServer/httpData.h
        httpServer/httpRequest.h
        httpServer/httpRequestHandler.h
        httpServer/httpRequestRouter.h
        httpServer/httpResponse.h
        httpServer/httpServer.h
        httpServer/httpServerConfig.h
        httpServer/middleware.h
        httpServer/util.h
)

set(HEADERS
        httpServer/const.h
        httpServer/httpConnection.h
        httpServer/httpCookie.h
        httpServer/httpData.h
        httpServer/httpRequest.h
        httpServer/httpRequestHandler.h
        httpServer/httpRequestRouter.h
        httpServer/httpResponse.h
        httpServer/httpServer.h
        httpServer/httpServerConfig.h
        httpServer/middleware.h
        httpServer/util.h
)

add_library(httpServer::httpServer ALIAS httpServer)

set_target_properties(httpServer
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    PUBLIC_HEADER "${HEADERS}"
)


target_compile_definitions(httpServer
    PRIVATE
        HTTPSERVER_LIBRARY
        QT_DEPRECATED_WARNINGS
)

target_link_libraries(httpServer
    PUBLIC
        Qt5::Core
        Qt5::Network
        ZLIB::ZLIB
        qtpromise::qtpromise
)

target_include_directories(httpServer
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

include(GNUInstallDirs)
install(TARGETS httpServer
    EXPORT httpServer_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/httpServer COMPONENT Development
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/httpServerConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/httpServerConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/httpServerConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/httpServer/cmake
)
install(
    FILES "${PROJECT_BINARY_DIR}/httpServerConfig.cmake"
          "${PROJECT_BINARY_DIR}/httpServerConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/httpServer/cmake
)

install(EXPORT httpServer_Targets
    FILE httpServerTargets.cmake
    NAMESPACE httpServer::
    DESTINATION share/httpServer/cmake
)
