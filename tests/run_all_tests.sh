#!/bin/bash

rm -rf build-all-tests
mkdir -p build-all-tests
cd build-all-tests
cmake .. || exit 1
make -j6 || exit 1

echo ==================================================================
vlibs/vgeometry/tests/tests_vgeometry
echo ==================================================================
vlibs/vgio/keyfile/test_keyfile/test_keyfile
echo ==================================================================
vlibs/vcrc/test_vcrc/test_vcrc
echo ==================================================================
vlibs/vstring/test_vstring/test_vstring
echo ==================================================================
vlibs/vpoints/test_vpoints/test_vpoints
echo ==================================================================
