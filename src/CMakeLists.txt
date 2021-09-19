cmake_minimum_required(VERSION "3.1.0")
project(gCosm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYMPHONY_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYMPHONY_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-rtsp-server-1.0 REQUIRED)

#add_executable(gCosm "main.cpp")

#include_directories("Parser")
#add_subdirectory(Parser)

#1
#set(SOURCES main.cpp)
#include_directories(Parser)
#add_executable(gCosm ${SOURCES})

include_directories(
        ${GLIB_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
)

include_directories(Parser
RTSP)

add_executable(gCosm main.cpp 
Parser/parser.cpp 
Parser/parser.h
Parser/ProgramConfig.h
RTSP/test.cpp 
RTSP/test.h)

target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})

