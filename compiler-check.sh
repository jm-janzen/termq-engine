#!/bin/sh -e

echo "Checking g++ ..."
CXX="g++"
make clean && make termq

echo "Checking clang++ ..."
CXX="clang++"
make clean && make termq

echo "All compilations passed."
exit 0

