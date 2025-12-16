# Circuit simulator

Simple C++ circuit simulator: a static library `circuit_lib` and two executables (`main`, `example`).

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

## Project layout
- CMakeLists.txt — build configuration
- include/ — public headers (e.g. `Circuit.hpp`)
- src/ — library and example sources (e.g. `Element.cpp`, `main.cpp`, `example.cpp`)
- build/ — out-of-source build directory (generated)

## Notes
- The library target is `circuit_lib` (STATIC) and is linked to Eigen3.
- Compiler warnings for the library: `-Wall -Wextra -Wpedantic`.