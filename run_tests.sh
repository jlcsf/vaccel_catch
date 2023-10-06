#!/bin/bash
# rm build -rf
mkdir -p build
cd build
cmake ../ -DBUILD_PLUGIN_NOOP=ON -DENABLE_TESTS=ON -DBUILD_EXAMPLES=ON
make
echo -e "\e[91m Test \e[0m"  
./tests
echo -e "\e[91m Plugin Test \e[0m"  
./test_plugins
echo -e "\e[91m Session Test \e[0m"
./test_session
echo -e "\e[91m Misc test \e[0m"
./test_misc   