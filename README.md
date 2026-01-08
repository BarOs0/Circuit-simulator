# Circuit simulator

Basic C++ circuit simulator: a static library `circuit_lib` and two executables (`main`, `example`).

## Requirements (Linux)
- cmake >= 3.10
- g++ with C++17 support
- Eigen3 (package: `libeigen3-dev`)
- build-essential

Install on Debian/Ubuntu:
```sh
sudo apt update
sudo apt install build-essential cmake libeigen3-dev
```

## Build
From the project root:
```sh
mkdir build
cd build
cmake ..
make
```
This uses C++17, finds Eigen3, builds a static library `circuit_lib` and executables `main` and `example`.

## Run
From the `build` directory:
```sh
./main
./example
```

## Documentation
For API detatils create a doxygen documentation from the project root:
```sh
doxygen -g
doxygen Doxyfile
```

## Project layout
- CMakeLists.txt - build configuration
- include/ - header files (e.g. `Circuit.hpp`)
- src/ - library and user sources (e.g. `Element.cpp`, `main.cpp`, `example.cpp`)
- build/ - out-of-source build directory (generated)
- /src/example.cpp - sample file with user manual
- /src/main.cpp - your playground, a file in which you can create your netlists
- .vscode - minimal vscode configuration (linux, cpp 17, eigen3)
- docs/ - directory with pdf documentation and UMLs

## Usage
- See example netlist code from the project root:
```sh
code /src/example.cpp
```
- Create your netlist from the project root:
```sh
code /src/main.cpp
```
- Compile and run your netlist
```sh
cd build
make
./main
```

