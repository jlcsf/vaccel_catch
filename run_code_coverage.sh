#!/bin/bash

mkdir build/coverage_data

find build -type f -name "*.gcda" -exec cp {} build/coverage_data/ \;
find build -type f -name "*.gcno" -exec cp {} build/coverage_data/ \;

cd build/

lcov -b ../src -c -d coverage_data -o total_coverage.info
lcov --remove total_coverage.info "/usr/include/*" "*/build/_deps/*" -o total_coverage_filtered.info
genhtml total_coverage_filtered.info --output-directory coverage_report


rm ../../vaccel_code_coverage/coverage_report -rf
cp -r coverage_report/* ../../vaccel_code_coverage

cd ../