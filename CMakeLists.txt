cmake_minimum_required(VERSION 3.30)
project(C3_IA_TBM)

set(CMAKE_CXX_STANDARD 20)


set(SFML_ROOT "/opt/homebrew/Cellar/sfml/3.0.0_1")


find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)


message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")


add_executable(C3_IA_TBM
        main.cpp
        Position.h
        Direction.h
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h
        Bug.h
        Hopper.cpp
        Hopper.h
        CrissCross.cpp
        CrissCross.h
        SuperBug.cpp
        SuperBug.h
        SFML.h
        SFML.cpp
)


target_link_libraries(C3_IA_TBM
        SFML::Graphics
        SFML::Window
        SFML::System
)


find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)
find_library(CARBON_LIBRARY Carbon)
target_link_libraries(C3_IA_TBM
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CARBON_LIBRARY}
)