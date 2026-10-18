cmake_minimum_required(VERSION 4.0)
project(SMO)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(SMO main.cpp
        Request.h
        Node.h
        Queue.h
        Request.cpp
        Queue.cpp
        ServiceChannel.h
        ServiceChannel.cpp
        mainwindow.h
        mainwindow.cpp)

target_link_libraries(SMO PRIVATE Qt6::Core Qt6::Widgets)
