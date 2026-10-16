cmake_minimum_required(VERSION 4.0)
project(SMO)

set(CMAKE_CXX_STANDARD 20)

add_executable(SMO main.cpp
        Request.h
        Node.h
        Queue.h
        Request.cpp
        Queue.cpp
        ServiceChannel.h
        ServiceChannel.cpp)
