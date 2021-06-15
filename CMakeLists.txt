cmake_minimum_required(VERSION 3.14)

project(httpServer
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(HttpServer_FetchQtPromise "Incorporate QtPromise lib via FetchContent" OFF)
option(HttpServer_UseGoldLinker OFF)
option(HttpServer_BuildTests ON)

include(FetchContent)
include(GNUInstallDirs)

if (HttpServer_UseGoldLinker)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
endif()


if (HttpServer_FetchQtPromise )
    message(" QtPromise via FetchContent")
    FetchContent_Declare(qtpromise
        GIT_REPOSITORY https://github.com/marc-cpdesign/qtpromise.git
        GIT_TAG a94ed16e63b67d9cc02bb2aab363e36169be222b
        GIT_SHALLOW true
    )

    # CMake v3.14+
    FetchContent_MakeAvailable(qtpromise)
else()
    message(" QtPromise via find_package")
    find_package(qtpromise REQUIRED)
endif()

find_package(PkgConfig)
find_package(ZLIB REQUIRED)

find_package(Qt5
    COMPONENTS
        Core
        Network
    REQUIRED
)

add_subdirectory(src)

if(HttpServer_BuildTests)
    add_subdirectory(test)
endif()
