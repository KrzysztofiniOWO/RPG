cmake_minimum_required(VERSION 3.22)
project(RPG)

set(CMAKE_CXX_STANDARD 14)

add_executable(RPG main.cpp Arena.cpp Monsters.cpp Arena.h Character.h Monsters.h RpgCommands.h RpgControl.h RpgViewer.h RpgCommands.cpp RpgControl.cpp RpgViewer.cpp)
