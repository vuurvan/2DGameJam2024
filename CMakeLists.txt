cmake_minimum_required(VERSION 3.7)

project(test)

find_package(SFML COMPONENTS window graphics audio system REQUIRED)

add_definitions(-DASSET_DIR="${CMAKE_SOURCE_DIR}/assets")

add_executable(test main.cpp
    headers/attack.hpp
    headers/boss.hpp
    headers/player.hpp
)

target_link_libraries(test
    sfml-graphics sfml-audio ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
)