#!/bin/sh -e

cd build
cmake ..
cmake --build .
ctest

