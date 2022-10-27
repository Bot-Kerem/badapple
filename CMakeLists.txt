cmake_minimum_required(VERSION 2.23)

find_package(OpenCV REQUIRED)

project(player)

include_directories( ${OpenCV_INCLUDE_DIRS} )
message(${OpenCV_INCLUDE_DIRS})

add_executable(player player.cpp)

target_link_libraries(player ${OpenCV_LIBS})

