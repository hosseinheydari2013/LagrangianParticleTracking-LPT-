cmake_minimum_required(VERSION 3.14)
project(SFML_LPT)

set(CMAKE_CXX_STANDARD 14)

add_executable(SFML_LPT main.cpp particles.cpp particles.h velocityField.h velocity.cpp velocity.h position.cpp position.h)

target_link_libraries(SFML_LPT
        "-framework sfml-graphics"
        "-framework sfml-system"
        "-framework sfml-window"
        )