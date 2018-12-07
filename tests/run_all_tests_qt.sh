#!/bin/bash

cd QtTests
rm Makefile
qmake . || exit 1
make -j6 || exit 1

echo ====================================================================================
test_vapplication_qt/test_vapplication_qt
rm test_vapplication_qt/Makefile
rm test_vapplication_qt/test_vapplication_qt
rm -r test_vapplication_qt/obj
echo ====================================================================================

rm Makefile
rm .qmake.stash
