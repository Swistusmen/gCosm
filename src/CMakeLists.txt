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
Common 
Server/RTSP
Server/AudioVideoSources  
Server
RTSP)

add_executable(gCosm main.cpp 
Parser/parser.cpp 
Parser/parser.h
Common/ProgramConfig.h
Common/DataChunk.h
Common/Utilities.h
Server/Server.h 
Server/Server.cpp
Server/StreamingServer.h 
Server/StreamingServer.cpp
Server/RTSP/RTSPServer.h 
Server/RTSP/RTSPServer.cpp 
Server/RTSP/RTSPSession.h 
Server/HLS/HLSServer.h 
Server/HLS/HLSServer.cpp
Server/PipelineManager/PipelineManager.h 
Server/PipelineManager/PipelineManager.cpp
)

target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})

