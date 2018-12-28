#!/bin/bash

rm -rf build-all-tests
mkdir -p build-all-tests
cd build-all-tests
cmake .. || exit 1
make -j6 || exit 1

echo ====================================================================================
vlibs/vgio/keyfile/test_keyfile/test_keyfile            || exit 1
echo ====================================================================================
vlibs/vcrc/test_vcrc/test_vcrc                          || exit 1
echo ====================================================================================
vlibs/vstring/test_vstring/test_vstring                 || exit 1
echo ====================================================================================
vlibs/vgeometry/test_vgeometry/test_vgeometry           || exit 1
echo ====================================================================================
vlibs/vapplication/test_vapplication/test_vapplication  || exit 1
echo ====================================================================================
vlibs/hdlc_parser/test_hdlc_parser/test_hdlc_parser     || exit 1
echo ====================================================================================
vlibs/vchrono/test_vchrono/test_vchrono                 || exit 1
echo ====================================================================================
echo
echo
echo ====================================================================================
echo  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
echo ====================================================================================
echo
echo "=                                      OK                                          ="
echo
echo ====================================================================================
echo  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
echo ====================================================================================
echo
exit 0
