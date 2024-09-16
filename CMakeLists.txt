cmake_minimum_required(VERSION 3.7)

project(test)

#find_package(SFML COMPONENTS window audio system REQUIRED)
add_executable(test main.cpp)

target_link_libraries(test
    #sfml-audio ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
)