#! /bin/bash

rm -rf ../cov
mkdir ../cov

# CLEAN: remove .da and gcda files and subdirectories
lcov --directory ../test/build/ --directory ../src/build/ --zerocounters
rm ../test/build/*.gcda
rm ../src/build/*.gcda

# run test
../test/build/test.exe --gtest_output=xml:../test/build/results.xml

# capture result
lcov --directory ../src/build/ --capture --output-file ../cov/app.info
cd ../cov
genhtml app.info
