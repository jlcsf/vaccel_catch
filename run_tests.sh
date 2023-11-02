#!/bin/bash


rm -rf build
mkdir -p build
cd build
cmake ../ -DBUILD_PLUGIN_NOOP=ON -DENABLE_TESTS=ON
make
# export VACCEL_BACKENDS=./plugins/noop/libvaccel-noop.so
# export VACCEL_DEBUG_LEVEL=4
make test

# test_targets=(
#   "tests"
#   "test_plugins"
#   "test_fpga"
#   "test_session"
#   "test_misc"
#   "test_resource"
#   "test_id_pool"
#   "test_log"
#   "test_vaccel"
# )


# mkdir -p coverage_data

# for target in "${test_targets[@]}"; do
#   echo -e "\e[91m Running $target \e[0m"
#   ./"$target"
# done



## for code coverage -- just manually upload for now.

cd ../
sh ./run_code_coverage.sh
