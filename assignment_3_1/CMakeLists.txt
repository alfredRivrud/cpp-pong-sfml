cmake_minimum_required(VERSION 4.1)
project(assignment_3_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment_3_1 main.cpp
        game.cpp
        game.h
        entity.h
        ball.cpp
        ball.h
        paddle.cpp
        paddle.h
        constants.h)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(assignment_3_1 PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
