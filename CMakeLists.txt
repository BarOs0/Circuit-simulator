#Minimum CMake version
cmake_minimum_required(VERSION 3.10)

#<project name> <project version> <programming language for C++ -> CXX>
project(CircuitSimulator VERSION 1.0 LANGUAGES CXX) 

#Compile with flag -std=c++17
set(CMAKE_CXX_STANDARD 17)

#If compiler does not support C++17 throw an error (no fallbacks)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ${PROJECT_SOURCE_DIR} - main project directory
# ${PROJECT_SOURCE_DIR}/include - .hpp files directory
# This allows us to use #include "Element.hpp" instead of #include "../include/Element.hpp"
include_directories(${PROJECT_SOURCE_DIR}/include)

#Creating variable SOURCES
#Everything in SOURCES will be compiled
set(SOURCES
    src/Element.cpp
    src/Passive.cpp
    src/Active.cpp
    src/Resistance.cpp
    src/Capacitance.cpp
    src/Inductance.cpp
    src/IndependantV.cpp
    src/IndependantJ.cpp
    src/Circuit.cpp
    src/main.cpp
)

#Creating executable file "circuit_simulator"
#Output location depends on where cmake is run (typically /build)
add_executable(circuit_simulator ${SOURCES})

#Compiler warnings
#MSVC (Windows, Visual Studio)
#GCC Linux
#Clang macOS
#-Wall -> all standard warnings
#-Wextra -> additional warnings
#-Wpedantic -> strict compliance with C++ standard
if(MSVC)
    #Windows Visual Studio (MSVC)
    target_compile_options(circuit_simulator PRIVATE /W4)
else()
    # Linux (GCC) & macOS (Clang)
    target_compile_options(circuit_simulator PRIVATE -Wall -Wextra -Wpedantic)
endif()

#CMake is supposed to be launched in /build directory
#Usage: mkdir build && cd build && cmake .. && make