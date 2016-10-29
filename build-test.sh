#!/bin/sh -e

# TODO take args to [build] [run] [test]

cd build
cmake ..
cmake --build .
ctest

