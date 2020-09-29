#!/bin/bash

# Create temporary directories for building
mkdir -p build
mkdir -p bin

# Use CMake and a Makefile to compile
cd build
cmake ..
make

echo "Built target in ./bin/"
