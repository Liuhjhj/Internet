cmake_minimum_required(VERSION 3.5)

project(IPcast LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
link_libraries("ws2_32")
add_executable(IPcast
  main.cpp
  widget.cpp
  widget.h
  widget.ui
  ipcast.cpp
  ipcast.h
)

target_link_libraries(IPcast PRIVATE Qt5::Widgets)
