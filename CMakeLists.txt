#Minimum CMake version
cmake_minimum_required(VERSION 3.10)

#<project name> <project version> <programming language for C++ -> CXX>
project(CircuitSimulator VERSION 1.0 LANGUAGES CXX) 

#Compile with flag -std=c++17
set(CMAKE_CXX_STANDARD 17)

#If compiler does not support C++17 throw an error (no fallbacks)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Solving Matrix equations with Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

#Creating variable LIB_SOURCES
set(LIB_SOURCES
    src/Element.cpp
    src/Passive.cpp
    src/Active.cpp
    src/Resistance.cpp
    src/Capacitance.cpp
    src/Inductance.cpp
    src/IndependentV.cpp
    src/IndependentJ.cpp
    src/Circuit.cpp
)

set(EXAMPLE_SOURCES
    src/example.cpp
)

#Creating variable APP_SOURCES
set(APP_SOURCES
    src/main.cpp
)

#Creating my own library
add_library(circuit_lib STATIC ${LIB_SOURCES})
target_include_directories(circuit_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(circuit_lib PUBLIC Eigen3::Eigen)
target_compile_options(circuit_lib PUBLIC -Wall -Wextra -Wpedantic)

# Creating executables and linking to the library
add_executable(main ${APP_SOURCES})
target_link_libraries(main PRIVATE circuit_lib)

add_executable(example ${EXAMPLE_SOURCES})
target_link_libraries(example PRIVATE circuit_lib)