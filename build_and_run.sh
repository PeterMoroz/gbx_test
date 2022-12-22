cd /home/gbx_test
rm -rf _build
mkdir _build
cd _build
cmake ../src
cmake --build .
CTEST_OUTPUT_ON_FAILURE=TRUE cmake --build . --target test
