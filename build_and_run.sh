#!/bin/bash

pg_ctlcluster 13 main start

cd /home/gbx_test
rm -rf _build
mkdir _build
cd _build
conan install .. --build missing -s compiler=gcc -s compiler.version=10.2 -s compiler.libcxx=libstdc++11
cmake ..
cmake --build .
CTEST_OUTPUT_ON_FAILURE=TRUE cmake --build . --target test
./bin/gbx_main
