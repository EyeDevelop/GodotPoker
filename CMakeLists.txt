cmake_minimum_required(VERSION 3.13)

project(GodotPoker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCE_FILES src)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)

add_library(godotpoker
        src/logic/card/card.cpp
        src/logic/card/deck.cpp
        src/logic/player/player.cpp
        src/logic/manager/manager.cpp
        src/godot/godot_poker.cpp
        )

add_executable(game
        src/logic/card/card.cpp
        src/logic/card/deck.cpp
        src/logic/player/player.cpp
        src/logic/manager/manager.cpp)

target_link_libraries(godotpoker
        libgodot-linux64.a)

#target_include_directories(godotpoker PRIVATE
#        godot-cpp/include
#        godot-cpp/godot_headers)