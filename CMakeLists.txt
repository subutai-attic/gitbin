cmake_minimum_required(VERSION 3.2)
project(git_bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("include")

set(SOURCE_FILES src/main.cpp)
add_executable(git_bin ${SOURCE_FILES} src/AWSFileTransfer.cpp src/FileTransfer.cpp src/Plugin.cpp src/S3FileTransfer.cpp include/AWSFileTransfer.h include/FileTransfer.h include/Plugin.h include/S3FileTransfer.h)

set(POCO "/usr/local/lib")

target_link_libraries(git_bin ${POCO}/libPocoFoundation.so)
target_link_libraries(git_bin ${POCO}/libPocoUtil.so)
target_link_libraries(git_bin ${POCO}/libPocoXML.so)
target_link_libraries(git_bin ${POCO}/libPocoJSON.so)