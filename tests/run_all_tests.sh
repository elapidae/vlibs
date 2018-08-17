#!/bin/bash

rm -rf build-all-tests
mkdir -p build-all-tests
cd build-all-tests
cmake .. || exit 1
make -j6 || exit 1


vlibs/vgeometry/tests/tests_vgeometry
vlibs/vgio/keyfile/test_keyfile/test_keyfile
