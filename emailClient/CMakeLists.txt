cmake_minimum_required(VERSION 3.5)

project(emailClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
link_libraries("ws2_32")
add_executable(emailClient
  main.cpp
  widget.cpp
  widget.h
  widget.ui
  sendemail.cpp
  sendemail.h
  base64.cpp
  base64.h
  mainmenu.cpp
  mainmenu.h
  mainmenu.ui
  recvemail.cpp
  recvemail.h
  recvemail.ui
  recvthread.cpp
  recvthread.h
)

target_link_libraries(emailClient PRIVATE Qt5::Widgets)
