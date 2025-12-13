cmake_minimum_required(VERSION 4.0)
project(arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FLTK REQUIRED)

set(TARGET "arkanoid")

add_executable(
        ${TARGET}
        main.cpp
        Graph_lib/Graph.cpp
        Graph_lib/GUI.cpp
        Graph_lib/Window.cpp
        ArkanoidWindow.cpp
        Platform.cpp
        StartScreen.cpp
        GameScreen.cpp
        Ball.cpp
        Block.cpp
)

target_include_directories(${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${FLTK_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/Graph_lib
)

target_link_libraries(${TARGET} PRIVATE
        ${FLTK_LIBRARIES}
)

