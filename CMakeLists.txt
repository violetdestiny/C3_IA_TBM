cmake_minimum_required(VERSION 3.30)
project(C3_IA_TBM)

set(CMAKE_CXX_STANDARD 20)


add_executable(C3_IA_TBM
        main.cpp
        Bug.h
        Crawler.cpp Crawler.h
        Hopper.cpp Hopper.h
        CrissCross.cpp CrissCross.h
        Board.cpp Board.h
        Position.h
        Direction.h
        SFML.cpp SFML.h
        SuperBug.cpp
        SuperBug.h
)


set(SFML_DIR "C:/SFML/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)


target_include_directories(C3_IA_TBM PRIVATE
        "C:/SFML/SFML-2.6.2/include"
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(C3_IA_TBM PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)
