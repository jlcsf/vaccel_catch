#!/bin/bash

export CXX=g++
rm build -rf
mkdir -p build
cd build
cmake ../ -DBUILD_PLUGIN_NOOP=ON -DENABLE_TESTS=ON -DBUILD_EXAMPLES=ON
make
make test ARGS="-V"
# make CTEST_OUTPUT_ON_FAILURE=1 test

cd ../
sh ./run_code_coverage.sh
