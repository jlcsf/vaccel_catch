#!/bin/bash
rm build -rf
mkdir -p build
cd build
cmake ../ -DBUILD_PLUGIN_NOOP=ON -DENABLE_TESTS=ON
make
echo -e "\e[91m Test \e[0m"  
./tests
echo -e "\e[91m Plugin Test \e[0m"  
./test_plugins
echo -e "\e[91m Session Test \e[0m"
./test_session
echo -e "\e[91m Misc test \e[0m"
./test_misc
echo -e "\e[91m Resource test \e[0m"
./test_resource



export VACCEL_BACKENDS=./plugins/noop/libvaccel-noop.so
echo -e "\e[91m FPGA plugin test \e[0m"
./test_fpga


export VACCEL_DEBUG_LEVEL=4
echo -e "\e[91m Vaccel test \e[0m"
./test_vaccel