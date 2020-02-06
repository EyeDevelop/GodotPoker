cmake_minimum_required(VERSION 3.13)

project(GodotPoker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCE_FILES src)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)

add_executable(GodotPoker
        src/logic/card/card.cpp
        src/logic/card/deck.cpp
        src/logic/player/player.cpp
        src/logic/manager/manager.cpp
        )