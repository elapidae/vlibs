#!/bin/bash

rm -rf build-all-tests
mkdir -p build-all-tests
cd build-all-tests
cmake ..
make -j6


vlibs/vgeometry/tests/tests_vgeometry
vlibs/vgio/keyfile/test_keyfile/test_keyfile
