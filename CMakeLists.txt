cmake_minimum_required(VERSION 3.30)
project(C3_IA_TBM)

set(CMAKE_CXX_STANDARD 20)

add_executable(C3_IA_TBM main.cpp
        Position.h
        Direction.h
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h)
