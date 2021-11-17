cmake_minimum_required(VERSION "3.9")
project(gCosm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#were neccesary for gstreamer, caused bugs when linking file with cpp rest sdk
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYMPHONY_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYMPHONY_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

find_package(cpprestsdk REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-rtsp-server-1.0 REQUIRED)

set_target_properties(cpprestsdk::cpprestsdk_openssl_internal PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "CPPREST_NO_SSL_LEAK_SUPPRESS"
  INTERFACE_LINK_LIBRARIES "OpenSSL::SSL"
)

include_directories(
        ${GLIB_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
        #${cpprestsdk}
        #${cpprestsdk_openssl_internal}
        #${CPPREST_NO_SSL_LEAK_SUPPRESS}
)

include_directories(Parser
Common 
Server
Server/RTSP
Server/HLS
Server/PipelineManager  
Server/HTTP
Transcoder
)

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
Server/HTTP/HTTPServer.cpp
Server/HTTP/HTTPServer.h 
Server/PipelineManager/PipelineManager.h 
Server/PipelineManager/PipelineManager.cpp
Transcoder/Transcoder.h 
Transcoder/Transcoder.cpp
)

target_link_libraries(${PROJECT_NAME} cpprestsdk::cpprest)
target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})


