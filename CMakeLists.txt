cmake_minimum_required(VERSION 3.16)
project(SpacecraftSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to a Release build if the user didn't specify one.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find system SFML 3 (install: pacman -S sfml / apt install libsfml-dev).
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(SpacecraftSimulator
    SpacecraftSimulator/main.cpp
    SpacecraftSimulator/Application.cpp
    SpacecraftSimulator/Camera.cpp
    SpacecraftSimulator/Renderer.cpp
    SpacecraftSimulator/Simulation.cpp
)

# Headers are included relative to the source dir, e.g. "simulation/Simulation.hpp".
target_include_directories(SpacecraftSimulator PRIVATE SpacecraftSimulator)

target_link_libraries(SpacecraftSimulator PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
