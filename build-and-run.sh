#!/bin/sh

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 5
./build/FireSimulation