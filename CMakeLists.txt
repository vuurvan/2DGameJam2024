cmake_minimum_required(VERSION 3.7)

project(test)

add_executable(test main.cpp
    headers/attack.hpp
    headers/boss.hpp
    headers/player.hpp
)

target_link_libraries(test)